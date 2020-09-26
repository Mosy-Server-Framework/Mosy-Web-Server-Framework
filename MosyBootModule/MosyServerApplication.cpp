#include "pch.h"
#include "MosyServerApplication.h"
#include "CoreStruct.h"
#include "MosyMessageQueue.h"

LONG WINAPI MosyUnhandledExceptionFilter(EXCEPTION_POINTERS* exp);

void MosyServerApplication::Boot()
{
	MosyLogger::BootLogo();
	CoreStruct Struct;
	MosyMessageQueue MessageQueue;
	Struct.MessageQueue = &MessageQueue;
	Struct.ThreadManager = &MosyGobalManager::ThreadManager;
	MosyGobalManager::ThreadManager.Manager = Struct.ThreadManager;
	HANDLE Receiver = MosyGobalManager::ThreadManager.CreateCoreThread(ReceiverThread, &Struct);
	//HANDLE Sender = MosyGobalManager::ThreadManager.CreateCoreThread(SenderThread, &Struct);
	::SetUnhandledExceptionFilter(MosyUnhandledExceptionFilter);
	if (Receiver == NULL)
	{
		MosyLogger::Log(MosyValue(L"FATAL ERROR: Core Thread(Receiver) Cannot be Started!"));
	}
	else
	{
		WaitForSingleObject(Receiver, INFINITE);
	}
}

LONG WINAPI MosyUnhandledExceptionFilter(EXCEPTION_POINTERS* exp)
{
	MosyLogger::Log(MosyValue(L"Something Error"));
	return EXCEPTION_EXECUTE_HANDLER;
}