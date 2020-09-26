#pragma once
#include "MosyObject.h"
#include "MosySocket.h"
#include "MosyResponsePackage.h"

class _declspec(dllimport) MosyResponseQueuePackage :
	public MosyObject
{
public:
	MosySocket ClientSocket;//Response Target Client Socket
	MosyResponsePackage Package;//Response Data Package
	MosyResponseQueuePackage();
	~MosyResponseQueuePackage();
};

