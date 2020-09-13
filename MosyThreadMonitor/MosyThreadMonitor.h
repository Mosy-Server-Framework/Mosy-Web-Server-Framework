#pragma once
#include "pch.h"
#include "MosyMonitorThreadStruct.h"
#include "MosyThreadManager.h"
#include "MosyGobalManager.h"

DWORD _stdcall MonitorThread(LPVOID LParam)
{
	MosyMonitorStruct* MonitorStruct = (MosyMonitorStruct*)LParam;
	HANDLE TargetThread = MonitorStruct->ThreadHandle;
	WaitForSingleObject(TargetThread, MosyGobalManager::RegistryManager.Query(MosyValue(L"ThreadResponseTimeout")).GetInteger());
	MosyGobalManager::ThreadManager.Remove(TargetThread);
	return 0;
}