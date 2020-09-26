#ifndef DLL_FILE
#define DLL_FILE
#endif
#include "pch.h"
#include "MosyServerSocket.h"

void MosyServerSocket::BindServer()
{
	BindServer(Port);
}

void MosyServerSocket::BindServer(int Port)
{
	Bind(Port);
}

void MosyServerSocket::SetupServerSocket()
{
	SetupSocket();
}

void MosyServerSocket::ListenServer()
{
	Listen();
}

MosySocket MosyServerSocket::Accept()
{
	sockaddr_in Client;
	int Len = sizeof(Client);
	SOCKET sAccept = accept(CoreSocket, (sockaddr*)&Client, &Len);
	if (sAccept == INVALID_SOCKET)
	{
		throw MosySocket::MosySocketException(MSE_INVALID_SOCKET, WSAGetLastError());
		return MosySocket();
	}
	return MosySocket(sAccept);
}

MosyServerSocket::MosyServerSocket()
{
	Port = 80;
}

MosyServerSocket::MosyServerSocket(int Port)
{
	this->Port = Port;
}

MosyServerSocket::MosyServerSocket(bool AutoBind)
{
	MosyServerSocket();
	if (AutoBind)
	{
		SetupServerSocket();
		BindServer();
		ListenServer();
	}
}

MosyServerSocket::MosyServerSocket(int TargetPort, bool AutoBind)
{
	Port = TargetPort;
	if (AutoBind)
	{
		SetupServerSocket();
		BindServer();
		ListenServer();
	}
}

MosyServerSocket::~MosyServerSocket()
{

}
