#pragma once
#include "pch.h"
#include "MosySocket.h"
#include "MosyMessageQueue.h"
#include "MosyThreadManager.h"

struct ThreadParamStruct
{
	SOCKET TargetSocket;
	MosyMessageQueue* MessageQueue;
	MosyThreadManager* ThreadManager;
};