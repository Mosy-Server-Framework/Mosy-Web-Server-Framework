#pragma once
#include "pch.h"
#include "MosyMonitorThreadStruct.h"
#include "MosyThreadMonitor.h"
#include <list>
using namespace std;



class _declspec(dllexport) MosyThreadManager
{
protected:
	list<HANDLE>* ThreadList;
public:
	MosyThreadManager* Manager;
	void Remove(HANDLE Item);
	bool CreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID LParam);
	HANDLE CreateCoreThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID LParam);
	MosyThreadManager();
	~MosyThreadManager();
};


struct MosyMonitorStruct
{
	HANDLE ThreadHandle;
	MosyThreadManager* Manager;
};