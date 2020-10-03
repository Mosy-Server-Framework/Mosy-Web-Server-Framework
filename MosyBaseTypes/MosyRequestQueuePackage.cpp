#include "..\MosyQueueManager\MosyRequestQueuePackage.h"
#include "pch.h"
#include "MosyRequestQueuePackage.h"

MosyRequestQueuePackage::MosyRequestQueuePackage()
{
}

MosyRequestQueuePackage::~MosyRequestQueuePackage()
{
}

void MosyRequestQueuePackage::operator=(MosyRequestQueuePackage p)
{
	ClientSocket = p.ClientSocket;
	Package = p.Package;
}
