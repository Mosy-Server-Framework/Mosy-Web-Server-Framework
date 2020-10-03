#pragma once
#include "MosyObject.h"
#include "MosyRequestPackage.h"
#include "MosySocket.h"

class _declspec(dllexport) MosyRequestQueuePackage :
	public MosyObject
{
public:
	SOCKET ClientSocket;
	MosyRequestPackage Package;
	MosyRequestQueuePackage();
	~MosyRequestQueuePackage();
	void operator=(MosyRequestQueuePackage p);
};

