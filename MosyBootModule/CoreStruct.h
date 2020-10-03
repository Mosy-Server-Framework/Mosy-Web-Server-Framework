#pragma once
#include "MosyThreadManager.h"
#include "MosyMessageQueue.h"
#include "MosyModuleManager.h"

struct CoreStruct {
	MosyThreadManager* ThreadManager;
	MosyMessageQueue* MessageQueue;
	MosyModuleManager* ModuleManager;
};