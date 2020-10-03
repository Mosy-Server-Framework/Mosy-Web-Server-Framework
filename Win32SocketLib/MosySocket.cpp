#ifndef DLL_FILE
#define DLL_FILE
#endif
#include "pch.h"
#include "MosySocket.h"
#pragma warning(disable:4996)

void MosySocket::SetupSocket() throw(MosySocketException)
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

void MosySocket::Listen() throw(MosySocketException)
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

void MosySocket::Bind() throw(MosySocketException)
{
	sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(Port);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
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

std::wstring MosySocket::Receive() throw(MosySocketException)
{
	if (HasConnected())
	{
		std::wstring RecvStr;
		char recv_buf[BUF_LENGTH];
		memset(recv_buf, 0, sizeof(recv_buf));
		int Result = recv(CoreSocket, recv_buf, sizeof(recv_buf), 0);
		if (Result == SOCKET_ERROR)
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

void MosySocket::Send(std::wstring Msg) throw(MosySocketException)
{
	if (HasConnected())
	{
		std::string snd = WString2String(Msg);
		send(CoreSocket, snd.c_str(), snd.length(), 0);
	}
}

void MosySocket::Send(std::string Msg) throw(MosySocketException)
{
	if (HasConnected())
	{
		send(CoreSocket, Msg.c_str(), Msg.length(), 0);
	}
}

DWORD MosySocket::GetStatusCode() throw(MosySocketException)
{
	return ConnectStatus;
}

MosySocket::MosySocket(SOCKET Socket) throw(MosySocketException)
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

void MosySocket::Send(std::vector<char> Msg, int size)
{
	if (HasConnected())
	{
		send(CoreSocket, Msg.data(), size, 0);
	}
}

MosySocket::MosySocket()
{
}

int MosySocket::GetConnectPort()
{
	if (HasConnected())
	{
		struct sockaddr_in sa;
		int len = sizeof(sa);
		if (!getpeername(CoreSocket, (struct sockaddr *)&sa, &len))
		{
			return ntohs(sa.sin_port);
		}
	}
	else
	{
		throw MosySocketException(MSE_ERROR);
	}
	return 0;
}

wstring MosySocket::GetConnectAddr()
{
	if (HasConnected())
	{
		struct sockaddr_in sa;
		int len = sizeof(sa);
		if (!getpeername(CoreSocket, (struct sockaddr *)&sa, &len))
		{
			return String2WString(inet_ntoa(sa.sin_addr));
		}
	}
	else
	{
		throw MosySocketException(MSE_ERROR);
	}
	return wstring();
}

MosySocket::MosySocket(MosySocket* Source) throw(MosySocketException)
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

void MosySocket::operator=(MosySocket * Source) throw(MosySocketException)
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

void MosySocket::Close() throw(MosySocketException)
{
	closesocket(CoreSocket);
	CoreSocket = INVALID_SOCKET;
}

SOCKET MosySocket::GetHandler() throw(MosySocketException)
{
	return CoreSocket;
}
