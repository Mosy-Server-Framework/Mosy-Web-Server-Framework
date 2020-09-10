#pragma once
#include "MosyObject.h"
#include "MosyRequestPackage.h"
#include "MosySocket.h"

class _declspec(dllexport) MosyRequestQueuePackage :
	public MosyObject
{
public:
	MosySocket ClientSocket;
	MosyRequestPackage Package;
	MosyRequestQueuePackage();
	~MosyRequestQueuePackage();
};

