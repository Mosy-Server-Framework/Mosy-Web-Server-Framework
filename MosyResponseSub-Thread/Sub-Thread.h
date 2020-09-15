#pragma once
#include "pch.h"
#include "MosyMessageQueue.h"
#include "MosyRequestPackage.h"
#include "MosyRequestQueuePackage.h"
#include "MosyResponsePackage.h"
#include "MosyResponseQueuePackage.h"
#include "MosySocket.h"
#include "MosyRequestDeserializer.h"
#include "MosyResponseSerializer.h"
#include "MosyDataPackage.h"
#include "MosyHtmlPackage.h"
#include "MosyDataSerializer.h"
#include "ThreadStruct.h"
#include <string.h>
using namespace std;

DWORD _stdcall RequestInitThread(LPVOID Param)
{
	ThreadParamStruct* ParamStruct = (ThreadParamStruct*)Param;
	MosySocket Socket(ParamStruct->TargetSocket);
	if (Socket.HasConnected())
	{
		wstring ReceiveData = Socket.Receive();
		MosyRequestPackage RequestPackage = MosyRequestDeserializer::Parse(ReceiveData);
		MosyRequestQueuePackage QueuePack;
		QueuePack.ClientSocket = ParamStruct->TargetSocket;
		QueuePack.Package = RequestPackage;
		ParamStruct->MessageQueue->PushRequestPackage(QueuePack);
	}
	return 0;
}

