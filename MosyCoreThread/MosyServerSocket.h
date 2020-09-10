#pragma once
#include "MosySocket.h"
#ifdef DLL_FILE
class _declspec(dllexport)
	MosyServerSocket :
	public MosySocket
#else
class _declspec(dllimport)
	MosyServerSocket :
	public MosySocket
#endif
{
public:
	void BindServer();
	void BindServer(int Port);
	void SetupServerSocket();
	void ListenServer();
	MosySocket Accept();
	MosyServerSocket();
	MosyServerSocket(int Port);
	MosyServerSocket(bool AutoBind);
	MosyServerSocket(int Port, bool AutoBind);
	~MosyServerSocket();
};

