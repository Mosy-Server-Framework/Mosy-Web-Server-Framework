#pragma once
#include <queue>
#include "MosyRequestQueuePackage.h"
#include "MosyResponseQueuePackage.h"
#include "MosyRequestPackage.h"
#include "MosyResponsePackage.h"
using namespace std;

class _declspec(dllexport) MosyMessageQueue
{
protected:
	queue<MosyRequestQueuePackage> RequestQueue;
	queue<MosyResponseQueuePackage> ResponseQueue;
	queue<SOCKET> SocketQueue;
public:
	void PushRequestPackage(MosyRequestQueuePackage Package);
	void PushResponsePackage(MosyResponseQueuePackage Package);
	MosyRequestQueuePackage GetRequestPackage();
	void PushRequestSocket(SOCKET Package);
	SOCKET GetRequestSocket();
	MosyResponseQueuePackage GetResponsePackage();
	int GetQueueLength();
	int GetSocketQueueLength();
	MosyMessageQueue();
	~MosyMessageQueue();
};

