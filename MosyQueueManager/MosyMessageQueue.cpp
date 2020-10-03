#include "pch.h"
#include "MosyMessageQueue.h"
CRITICAL_SECTION Critical;

void MosyMessageQueue::PushRequestPackage(MosyRequestQueuePackage Package)
{
	//EnterCriticalSection(&Critical);
	RequestQueue.push(Package);
	//LeaveCriticalSection(&Critical);
}

void MosyMessageQueue::PushResponsePackage(MosyResponseQueuePackage Package)
{
	//EnterCriticalSection(&Critical);
	ResponseQueue.push(Package);
	//LeaveCriticalSection(&Critical);
}

MosyRequestQueuePackage MosyMessageQueue::GetRequestPackage()
{
	MosyRequestQueuePackage Package = RequestQueue.front();
	//EnterCriticalSection(&Critical);
	RequestQueue.pop();
	//LeaveCriticalSection(&Critical);
	return Package;
}

void MosyMessageQueue::PushRequestSocket(SOCKET Package)
{
	//EnterCriticalSection(&Critical);
	SocketQueue.push(Package);
	//LeaveCriticalSection(&Critical);
}

SOCKET MosyMessageQueue::GetRequestSocket()
{
	if (SocketQueue.empty())
	{
		return INVALID_SOCKET;
	}
	SOCKET Package = SocketQueue.front();
	SocketQueue.pop();
	return Package;
}

MosyResponseQueuePackage MosyMessageQueue::GetResponsePackage()
{
	if (ResponseQueue.empty())
	{
		MosyResponseQueuePackage Package;
		return Package;
	}
	MosyResponseQueuePackage Package;
	if (&ResponseQueue.front() != NULL)
	{
		Package = ResponseQueue.front();
		//EnterCriticalSection(&Critical);
		ResponseQueue.pop();
		//LeaveCriticalSection(&Critical);
	}
	return Package;
}

int MosyMessageQueue::GetQueueLength()
{
	return ResponseQueue.size();
}

int MosyMessageQueue::GetSocketQueueLength()
{
	return SocketQueue.size();
}

MosyMessageQueue::MosyMessageQueue()
{
	InitializeCriticalSection(&Critical);
}

MosyMessageQueue::~MosyMessageQueue()
{
}
