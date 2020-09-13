// SimpleHTTPServer.cpp
// 功能：实现简单的web服务器功能，能同时响应多个浏览器的请求：
//       1、如果该文件存在，则在浏览器上显示该文件；
//       2、如果文件不存在，则返回404-file not found页面
//       3、只支持GET、HEAD方法
// HTTP1.1 与 1.0不同，默认是持续连接的(keep-alive)

#include "pch.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <direct.h>
#include "MosyServerSocket.h"
#include "MosySocket.h"
#include "MosyRequestPackage.h"
#include "MosyRequestDeserializer.h"
#include "MosyServerApplication.h"
#pragma warning(disable:4996)

#define DEFAULT_PORT 8088
#define USER_ERROR -1
#define SERVER "Server: csr_http1.1\r\n"

int file_not_found(MosySocket* sAccept);
int file_ok(MosySocket* sAccept, long flen);
int send_file(MosySocket* sAccept, FILE *resource);
int send_not_found(MosySocket* sAccept);

DWORD WINAPI SimpleHTTPServer(LPVOID lparam)
{
	SOCKET sAccept = (SOCKET)(LPVOID)lparam;
	MosySocket socket(sAccept);
	char recv_buf[BUF_LENGTH];
	char method[MIN_BUF];
	char url[MIN_BUF];
	char path[_MAX_PATH];
	int i, j;

	// 缓存清0，每次操作前都要记得清缓存，养成习惯；
	// 不清空可能出现的现象：输出乱码、换台机器乱码还各不相同
	// 原因：不清空会输出遇到 '\0'字符为止，所以前面的不是'\0' 也会一起输出
	std::wstring str = socket.Receive();
	MosyRequestPackage Pack = MosyRequestDeserializer::Parse(str);
	strcpy(recv_buf, MosyString::WString2String(((MosyValue*)Pack.Params[L"a"].obj())->GetString()).c_str());
	printf("recv data from client:%s\n", recv_buf); //接收成功，打印请求报文
	//处理接收数据
	i = 0; j = 0;
	// 取出第一个单词，一般为HEAD、GET、POST
	while (!(' ' == recv_buf[j]) && (i < sizeof(method) - 1))
	{
		method[i] = recv_buf[j];
		i++; j++;
	}
	method[i] = '\0';   // 结束符，这里也是初学者很容易忽视的地方

	// 如果不是GET或HEAD方法，则直接断开本次连接
	// 如果想做的规范些可以返回浏览器一个501未实现的报头和页面
	if (stricmp(method, "GET") && stricmp(method, "HEAD"))
	{
		socket.Close(); //释放连接套接字，结束与该客户的通信
		printf("not get or head method.\nclose ok.\n");
		printf("***********************\n\n\n\n");
		return USER_ERROR;
	}
	printf("method: %s\n", method);

	// 提取出第二个单词(url文件路径，空格结束)，并把'/'改为windows下的路径分隔符'\'
	// 这里只考虑静态请求(比如url中出现'?'表示非静态，需要调用CGI脚本，'?'后面的字符串表示参数，多个参数用'+'隔开
	// 例如：www.csr.com/cgi_bin/cgi?arg1+arg2 该方法有时也叫查询，早期常用于搜索)
	i = 0;
	while ((' ' == recv_buf[j]) && (j < sizeof(recv_buf)))
		j++;
	while (!(' ' == recv_buf[j]) && (i < sizeof(recv_buf) - 1) && (j < sizeof(recv_buf)))
	{
		if (recv_buf[j] == '/')
			url[i] = '\\';
		else if (recv_buf[j] == ' ')
			break;
		else
			url[i] = recv_buf[j];
		i++; j++;
	}
	url[i] = '\0';
	printf("url: %s\n", url);

	// 将请求的url路径转换为本地路径
	_getcwd(path, _MAX_PATH);
	strcat(path, url);
	printf("path: %s\n", path);

	// 打开本地路径下的文件，网络传输中用r文本方式打开会出错
	FILE *resource = fopen(path, "rb");

	// 没有该文件则发送一个简单的404-file not found的html页面，并断开本次连接
	if (resource == NULL)
	{
		file_not_found(&socket);
		// 如果method是GET，则发送自定义的file not found页面
		if (0 == stricmp(method, "GET"))
			send_not_found(&socket);

		socket.Close(); //释放连接套接字，结束与该客户的通信
		printf("file not found.\nclose ok.\n");
		printf("***********************\n\n\n\n");
		WSACleanup();
		return USER_ERROR;
	}

	// 求出文件长度，记得重置文件指针到文件头
	fseek(resource, 0, SEEK_SET);
	fseek(resource, 0, SEEK_END);
	long flen = ftell(resource);
	printf("file length: %ld\n", flen);
	fseek(resource, 0, SEEK_SET);

	// 发送200 OK HEAD
	file_ok(&socket, flen);

	// 如果是GET方法则发送请求的资源
	if (0 == stricmp(method, "GET"))
	{
		if (0 == send_file(&socket, resource))
			printf("file send ok.\n");
		else
			printf("file send fail.\n");
	}
	fclose(resource);

	socket.Close(); //释放连接套接字，结束与该客户的通信
	printf("close ok.\n");
	printf("***********************\n\n\n\n");

	WSACleanup();
	return 0;

}

// 发送404 file_not_found报头
int file_not_found(MosySocket* sAccept)
{
	char send_buf[MIN_BUF];
	sprintf(send_buf, "HTTP/1.1 404 NOT FOUND\r\n");
	sAccept->Send(send_buf);
	sprintf(send_buf, "Connection: keep-alive\r\n");
	sAccept->Send(send_buf);
	sprintf(send_buf, SERVER);
	sAccept->Send(send_buf);
	sprintf(send_buf, "Content-Type: text/html\r\n");
	sAccept->Send(send_buf);
	sprintf(send_buf, "\r\n");
	sAccept->Send(send_buf);
	return 0;
}

// 发送200 ok报头
int file_ok(MosySocket* sAccept, long flen)
{
	char send_buf[MIN_BUF];
	sprintf(send_buf, "HTTP/1.1 200 OK\r\n");
	sAccept->Send(send_buf);
	sprintf(send_buf, "Connection: keep-alive\r\n");
	sAccept->Send(send_buf);
	sprintf(send_buf, SERVER);
	sAccept->Send(send_buf);
	sprintf(send_buf, "Content-Length: %ld\r\n", flen);
	sAccept->Send(send_buf);
	sprintf(send_buf, "Content-Type: text/html\r\n");
	sAccept->Send(send_buf);
	sprintf(send_buf, "\r\n");
	sAccept->Send(send_buf);
	return 0;
}

// 发送自定义的file_not_found页面
int send_not_found(MosySocket* sAccept)
{
	char send_buf[MIN_BUF];
	sprintf(send_buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
	sAccept->Send(send_buf);
	sprintf(send_buf, "<BODY><h1 align='center'>404</h1><br/><h1 align='center'>file not found.</h1>\r\n");
	sAccept->Send(send_buf);
	sprintf(send_buf, "</BODY></HTML>\r\n");
	sAccept->Send(send_buf);
	return 0;
}

// 发送请求的资源
int send_file(MosySocket* sAccept, FILE *resource)
{
	char send_buf[BUF_LENGTH];
	while (1)
	{
		memset(send_buf, 0, sizeof(send_buf));       //缓存清0
		fgets(send_buf, sizeof(send_buf), resource);
		//  printf("send_buf: %s\n",send_buf);
		sAccept->Send(send_buf);
		if (feof(resource))
			return 0;
	}
}

int main()
{
	/*WSADATA wsaData;
	SOCKET sListen, sAccept;
	int serverport = DEFAULT_PORT;
	struct sockaddr_in ser, cli;
	int iLen;
	wchar_t szExeFilePathFileName[MAX_PATH];
	GetModuleFileNameW(NULL, szExeFilePathFileName, MAX_PATH);
	std::wstring str = szExeFilePathFileName;
	int idx = str.find_first_of('\\');
	std::wstring sss = str.substr(0, idx);
	SetCurrentDirectoryW(sss.c_str());
	printf("-----------------------\n");
	printf("Server waiting\n");
	printf("-----------------------\n");
	MosyServerSocket Server(serverport, true);
	while (1)
	{
		MosySocket sAccept = Server.Accept();
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (!sAccept.HasConnected())
		{
			printf("accept() Failed:%d\n", WSAGetLastError());
		}
		else
		{
			DWORD ThreadID;
			CreateThread(NULL, 0, SimpleHTTPServer, (LPVOID)sAccept.GetHandler(), 0, &ThreadID);
		}
	}
	Server.Close();
	WSACleanup();*/
	MosyServerApplication::Boot();
	return 0;
}