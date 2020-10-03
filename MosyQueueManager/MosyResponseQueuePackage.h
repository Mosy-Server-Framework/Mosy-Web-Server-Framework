#pragma once
#include "MosyObject.h"
#include "MosySocket.h"
#include "MosyResponsePackage.h"

class _declspec(dllimport) MosyResponseQueuePackage :
	public MosyObject
{
public:
	SOCKET ClientSocket;//Response Target Client Socket
	MosyResponsePackage Package;//Response Data Package
	MosyResponseQueuePackage();
	~MosyResponseQueuePackage();
	void operator=(MosyResponseQueuePackage p);
};

