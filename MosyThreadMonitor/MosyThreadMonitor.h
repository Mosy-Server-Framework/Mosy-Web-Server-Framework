#pragma once
#include "pch.h"
#include "MosyMonitorThreadStruct.h"
#include "MosyThreadManager.h"

DWORD _stdcall _declspec(dllexport) MonitorThread(LPVOID LParam)
{
	MosyMonitorStruct* MonitorStruct = (MosyMonitorStruct*)LParam;
	HANDLE TargetThread = MonitorStruct->ThreadHandle;
	WaitForSingleObject(TargetThread, INFINITE);
	MonitorStruct->Manager->Remove(TargetThread);
	return 0;
}