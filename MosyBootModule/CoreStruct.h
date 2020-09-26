#pragma once
#include "MosyThreadManager.h"
#include "MosyMessageQueue.h"

struct CoreStruct {
	MosyThreadManager* ThreadManager;
	MosyMessageQueue* MessageQueue;
};