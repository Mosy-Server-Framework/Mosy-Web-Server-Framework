#include "pch.h"
#include "MosyThreadManager.h"

void MosyThreadManager::Remove(HANDLE Item)
{
	list<HANDLE>::iterator iterator;
	iterator = ThreadList.begin();
	while (iterator != ThreadList.end())
	{
		if ((*iterator) == Item)
		{
			iterator = ThreadList.erase(iterator);
		}
		else
		{
			iterator++;
		}
	}
}

bool MosyThreadManager::CreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID LParam)
{

	return false;
}
