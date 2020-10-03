#ifndef DLL_FILE
#define DLL_FILE
#endif
#include "pch.h"
#include "MosyServerSocket.h"

void MosyServerSocket::BindServer() throw(MosySocketException)
{
	BindServer(Port);
}

void MosyServerSocket::BindServer(int Port) throw(MosySocketException)
{
	Bind(Port);
}

void MosyServerSocket::SetupServerSocket() throw(MosySocketException)
{
	SetupSocket();
}

void MosyServerSocket::ListenServer() throw(MosySocketException)
{
	Listen();
}

MosySocket MosyServerSocket::Accept() throw(MosySocketException)
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

MosyServerSocket::MosyServerSocket() throw(MosySocketException)
{
	Port = 80;
}

MosyServerSocket::MosyServerSocket(int Port) throw(MosySocketException)
{
	this->Port = Port;
}

MosyServerSocket::MosyServerSocket(bool AutoBind) throw(MosySocketException)
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
