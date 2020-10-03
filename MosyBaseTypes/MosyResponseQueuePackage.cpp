#include "pch.h"
#include "MosyResponseQueuePackage.h"

MosyResponseQueuePackage::MosyResponseQueuePackage()
{
}

MosyResponseQueuePackage::~MosyResponseQueuePackage()
{
}

void MosyResponseQueuePackage::operator=(MosyResponseQueuePackage p)
{
	ClientSocket = p.ClientSocket;
	Package = p.Package;
}
