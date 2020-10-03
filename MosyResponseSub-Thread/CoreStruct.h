#pragma once
#include "MosyThreadManager.h"
#include "MosyMessageQueue.h"
#include "MosyModuleManager.h"

struct CoreStruct {
	MosyThreadManager* ThreadManager;
	MosyMessageQueue* MessageQueue;
	MosyModuleManager* ModuleManager;
};

struct CoreSubSenderStruct {
	MosyThreadManager* ThreadManager;
	MosyMessageQueue* MessageQueue;
	int Index;
};