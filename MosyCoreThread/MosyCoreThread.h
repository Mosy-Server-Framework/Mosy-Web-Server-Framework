#pragma once
#include "MosyServerSocket.h"
#include "MosySocket.h"
#include "MosyArray.h"
#include "MosyMap.h"
#include "MosyObject.h"
#include "MosyGobalManager.h"
#include "MosyLogger.h"
#include "MosyRegistryManager.h"
#include "ThreadStruct.h"
#include "CoreStruct.h"
#include "MosyMessageQueue.h"
#pragma warning(disable:4996)

DWORD _declspec(dllimport) InitThread(LPVOID LParam);

DWORD __stdcall ReceiverThread(LPVOID LParam)
{
	MosyRegistryManager RegistryManager;
	int Port = RegistryManager.Query(MosyValue(L"Port")).GetInteger();
	MosyServerSocket ServerSocket(Port, true);
	CoreStruct* Core = (CoreStruct*)LParam;
	MosyThreadManager* ThreadManager = Core->ThreadManager;
	MosyMessageQueue* Queue = Core->MessageQueue;
	//MessageBox(NULL, L"ReceiverRun!", L"Run", MB_OK);
	char str[1000];
	sprintf(str, "Mosy Core Receiver Thread Started on Port %d", Port);
	MosyLogger::Log(MosyValue(MosyString::String2WString(str)));
	while (TRUE)
	{
		try
		{
			MosySocket sAccept = ServerSocket.Accept();
			/*WSADATA wsaData;
			WSAStartup(MAKEWORD(2, 2), &wsaData);*/
			if (!sAccept.HasConnected())
			{
				char str[1000];
				sprintf(str, "Accept Failed:%d", WSAGetLastError());
				MosyLogger::Log(MosyValue(MosyString::String2WString(str)));
				sAccept.Close();
			}
			else
			{
				//MosyLogger::Log(MosyValue(L""));
				//MosyLogger::Log(MosyValue(sAccept.Receive()));
				//MosyLogger::Log(MosyValue(L"Receive Data"));
				ThreadParamStruct Struct;
				Struct.Queue = Queue;
				Struct.TargetSocket = sAccept.GetHandler();
				SOCKET s = sAccept.GetHandler();
				Queue->PushRequestSocket(s);
				ThreadManager->CreateThread(InitThread, LParam);
			}
		}
		catch (MosySocket::MosySocketException e)
		{
			MosyLogger::Log(MosyValue(MosyString::String2WString(e.what())));
			/*ServerSocket.Close();
			ServerSocket.SetupServerSocket();
			ServerSocket.BindServer();
			ServerSocket.ListenServer();*/
		}
		catch (exception e)
		{
			MosyLogger::Log(MosyValue(MosyString::String2WString(e.what())));
		}
	}
	return 0;
}

DWORD __stdcall SubSenderThread(LPVOID LParam);

DWORD __stdcall SenderThread(LPVOID LParam)
{
	CoreStruct* Core = (CoreStruct*)LParam;
	MosyThreadManager* ThreadManager = Core->ThreadManager;
	MosyMessageQueue* Queue = Core->MessageQueue;
	//MessageBox(NULL, L"ReceiverRun!", L"Run", MB_OK);
	char str[1000];
	sprintf(str, "Mosy Core Sender Thread Started");
	MosyLogger::Log(MosyValue(MosyString::String2WString(str)));
	while (TRUE)
	{
		try
		{
			if (Queue->GetQueueLength() > 0)
			{
				ThreadManager->CreateCoreThread(SubSenderThread, LParam);
			}
		}
		catch (exception e)
		{
			MosyLogger::Log(MosyValue(MosyString::String2WString(e.what())));
		}
		Sleep(1);
	}
	return 0;
}

DWORD __stdcall SubSenderThread(LPVOID LParam)
{
	CoreStruct* Core = (CoreStruct*)LParam;
	MosyThreadManager* ThreadManager = Core->ThreadManager;
	MosyMessageQueue* Queue = Core->MessageQueue;
	//MessageBox(NULL, L"ReceiverRun!", L"Run", MB_OK);
	char str[1000];
	sprintf(str, "Mosy Sub Sender Thread Started");
	MosyLogger::Log(MosyValue(MosyString::String2WString(str)));
	while (TRUE)
	{
		try
		{
			if (Queue->GetQueueLength() == 0)
			{
				break;
			}
			if (Queue->GetQueueLength() > 0)
			{
				MosyResponseQueuePackage p = Queue->GetResponsePackage();
				MosySocket Socket(p.ClientSocket);
				if (Socket.HasConnected())
				{
					Socket.Send(p.Package.Head + p.Package.Body);
				}
				Socket.Close();
			}
		}
		catch (exception e)
		{
			MosyLogger::Log(MosyValue(MosyString::String2WString(e.what())));
		}
		Sleep(1);
	}
	MosyLogger::Log(MosyValue(L"Mosy Sub Sender Thread Terminal"));
	return 0;
}