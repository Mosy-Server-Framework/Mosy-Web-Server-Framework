#pragma once
#include "MosyThreadManager.h"

struct MosyMonitorStruct
{
	MosyThreadManager* Manager;
	HANDLE ThreadHandle;
};