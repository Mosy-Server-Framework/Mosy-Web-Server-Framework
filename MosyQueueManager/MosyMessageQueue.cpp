#include "pch.h"
#include "MosyMessageQueue.h"

void MosyMessageQueue::PushRequestPackage(MosyRequestQueuePackage Package)
{
	RequestQueue.push(Package);
}

void MosyMessageQueue::PushResponsePackage(MosyResponseQueuePackage Package)
{
	ResponseQueue.push(Package);
}

MosyRequestQueuePackage MosyMessageQueue::GetRequestPackage()
{
	MosyRequestQueuePackage Package = RequestQueue.front();
	RequestQueue.pop();
	return Package;
}

MosyResponseQueuePackage MosyMessageQueue::GetResponsePackage()
{
	MosyResponseQueuePackage Package = ResponseQueue.front();
	ResponseQueue.pop();
	return Package;
}

MosyMessageQueue::MosyMessageQueue()
{
}

MosyMessageQueue::~MosyMessageQueue()
{
}
