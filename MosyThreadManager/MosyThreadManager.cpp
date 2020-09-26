#include "pch.h"
#include "MosyThreadManager.h"

void MosyThreadManager::Remove(HANDLE Item)
{
	list<HANDLE>::iterator iterator;
	iterator = ThreadList->begin();
	while (iterator != ThreadList->end())
	{
		if ((*iterator) == Item)
		{
			iterator = ThreadList->erase(iterator);
		}
		else
		{
			iterator++;
		}
	}
}

bool MosyThreadManager::CreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID LParam)
{
	HANDLE CurrentHandle = ::CreateThread(NULL, NULL, lpStartAddress, LParam, NULL, NULL);
	if (CurrentHandle == NULL)
	{
		return false;
	}
	/*ThreadList->push_back(CurrentHandle);
	MosyMonitorStruct Monitor;
	Monitor.ThreadHandle = CurrentHandle;
	Monitor.Manager = Manager;
	HANDLE MonitorHandle = ::CreateThread(NULL, NULL, MonitorThread, &Monitor, NULL, NULL);
	if (MonitorHandle == NULL)
	{
		TerminateThread(CurrentHandle, 0);
		Remove(CurrentHandle);
		return false;
	}*/
	return true;
}

HANDLE MosyThreadManager::CreateCoreThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID LParam)
{
	HANDLE CurrentHandle = ::CreateThread(NULL, NULL, lpStartAddress, LParam, NULL, NULL);
	if (CurrentHandle == NULL)
	{
		return NULL;
	}
	/*ThreadList->push_back(CurrentHandle);
	MosyMonitorStruct Monitor;
	Monitor.ThreadHandle = CurrentHandle;
	Monitor.Manager = Manager;
	HANDLE MonitorHandle = ::CreateThread(NULL, NULL, MonitorThread, this, NULL, NULL);
	if (MonitorHandle == NULL)
	{
		TerminateThread(CurrentHandle, 0);
		Remove(CurrentHandle);
		return NULL;
	}*/
	return CurrentHandle;
}

MosyThreadManager::MosyThreadManager()
{
	ThreadList = new list<HANDLE>();
}

MosyThreadManager::~MosyThreadManager()
{
	if (ThreadList)
	{
		delete ThreadList;
	}
}
