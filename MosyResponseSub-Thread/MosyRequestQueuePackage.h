#pragma once
#include "MosyObject.h"
#include "MosyRequestPackage.h"
#include "MosySocket.h"

class _declspec(dllimport) MosyRequestQueuePackage :
	public MosyObject
{
public:
	MosySocket ClientSocket;
	MosyRequestPackage Package;
	MosyRequestQueuePackage();
	~MosyRequestQueuePackage();
};

