#pragma once
#include "pch.h"
#include "MosyMonitorThreadStruct.h"
#include "MosyThreadManager.h"
#include "MosyGobalManager.h"
#include "MosyLogger.h"

DWORD _stdcall MonitorThread(LPVOID LParam)
{
	MosyMonitorStruct* MonitorStruct = (MosyMonitorStruct*)LParam;
	HANDLE TargetThread = MonitorStruct->ThreadHandle;
	//MessageBox(NULL, L"MonitorRun!", L"Run", MB_OK);
	MosyLogger::Log(MosyValue(L"Monitor Execute"));
	WaitForSingleObject(TargetThread, INFINITE);
	MosyLogger::Log(MosyValue(L"Monitor Terminal"));
	MonitorStruct->Manager->Remove(TargetThread);
	return 0;
}