#ifndef DLL_FILE
#define DLL_FILE
#endif
#include "pch.h"
#include "MosySocket.h"

void MosySocket::SetupSocket()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw MosySocketException(MSE_FAILED_LOAD_WINSOCKET, WSAGetLastError());
		return;
	}
	CoreSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (CoreSocket == INVALID_SOCKET)
	{
		throw MosySocketException(MSE_INVALID_SOCKET, WSAGetLastError());
		return;
	}
}

void MosySocket::Listen()
{
	if (listen(CoreSocket, 5) == SOCKET_ERROR)
	{
		throw MosySocketException(MSE_FAILED_LISTEN, WSAGetLastError());
		return;
	}
}

void MosySocket::Bind(DWORD Port)
{
	this->Port = Port;
	Bind();
}

void MosySocket::Bind()
{
	sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(Port);               //服务器端口号
	ser.sin_addr.s_addr = htonl(INADDR_ANY);   //服务器IP地址，默认使用本机IP
	if (bind(CoreSocket, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		throw MosySocketException(MSE_FAILED_BIND, WSAGetLastError());
		return;
	}
}

DWORD MosySocket::GetPort()
{
	return Port;
}

void MosySocket::ShutDownSocket()
{
	WSACleanup();
}

MosySocket::~MosySocket()
{
}

bool MosySocket::HasConnected()
{
	return (CoreSocket != NULL && CoreSocket != INVALID_SOCKET);
}

std::wstring MosySocket::Receive()
{
	if (HasConnected())
	{
		std::wstring RecvStr;
		char recv_buf[BUF_LENGTH];
		memset(recv_buf, 0, sizeof(recv_buf));
		int Result = recv(CoreSocket, recv_buf, sizeof(recv_buf), 0);
		if (Result == SOCKET_ERROR)   //接收错误
		{
			throw MosySocketException(MSE_ERROR);
			return std::wstring();
		}
		else
		{
			std::string tstr = recv_buf;
			RecvStr += String2WString(tstr);
		}
		return RecvStr;
	}
	return std::wstring();
}

int Min(int a, int b)
{
	return (((a) < (b)) ? (a) : (b));
}

void MosySocket::Send(std::wstring Msg)
{
	if (HasConnected())
	{
		std::string snd = WString2String(Msg);
		send(CoreSocket, snd.c_str(), MIN_BUF, 0);
	}
}

void MosySocket::Send(std::string Msg)
{
	if (HasConnected())
	{
		send(CoreSocket, Msg.c_str(), Msg.length(), 0);
	}
}

DWORD MosySocket::GetStatusCode()
{
	return ConnectStatus;
}

MosySocket::MosySocket(SOCKET Socket)
{
	if (Socket == INVALID_SOCKET)
	{
		throw MosySocketException(MSE_INVALID_SOCKET, WSAGetLastError());
		return;
	}
	else
	{
		CoreSocket = Socket;
	}
}

MosySocket::MosySocket()
{
}

MosySocket::MosySocket(MosySocket* Source)
{
	if (Source->CoreSocket == INVALID_SOCKET)
	{
		throw MosySocketException(MSE_INVALID_SOCKET, WSAGetLastError());
		return;
	}
	else
	{
		CoreSocket = Source->CoreSocket;
		Port = Source->Port;
	}
}

void MosySocket::operator=(MosySocket * Source)
{
	if (Source->CoreSocket == INVALID_SOCKET)
	{
		throw MosySocketException(MSE_INVALID_SOCKET, WSAGetLastError());
		return;
	}
	else
	{
		CoreSocket = Source->CoreSocket;
		Port = Source->Port;
	}
}

void MosySocket::Close()
{
	closesocket(CoreSocket);
	CoreSocket = INVALID_SOCKET;
}

SOCKET MosySocket::GetHandler()
{
	return CoreSocket;
}
