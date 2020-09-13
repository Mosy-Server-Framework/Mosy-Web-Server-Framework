#include "pch.h"
#include "MosyServerApplication.h"

void MosyServerApplication::Boot()
{
	MosyLogger::BootLogo();
	HANDLE Receiver = MosyGobalManager::ThreadManager.CreateCoreThread(ReceiverThread, NULL);
	if (Receiver == NULL)
	{
		MosyLogger::Log(MosyValue(L"FATAL ERROR: Core Thread(Receiver) Cannot be Started!"));
	}
	else
	{
		WaitForSingleObject(Receiver, INFINITE);
	}
}
