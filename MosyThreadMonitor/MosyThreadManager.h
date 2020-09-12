#pragma once
#include "pch.h"
#include "MosyMonitorThreadStruct.h"
#include "list"
using namespace std;

class _declspec(dllexport) MosyThreadManager
{
protected:
	list<HANDLE> ThreadList;
public:
	void Remove(HANDLE Item);
	bool CreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID LParam);
};

