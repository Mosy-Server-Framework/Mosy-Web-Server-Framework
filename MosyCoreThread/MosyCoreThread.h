#pragma once
#include "MosyRequestDeserializer.h"
#include "MosyRequestPackage.h"
#include "MosyServerSocket.h"
#include "MosySocket.h"
#include "MosyArray.h"
#include "MosyMap.h"
#include "MosyObject.h"
#include "MosyHtmlPackage.h"
#include "MosyHtmlSerializer.h"
#include "MosyDataPackage.h"
#include "MosyDataSerializer.h"
#include "MosyGobalManager.h"
#include "MosyLogger.h"
#include "MosyRegistryManager.h"

DWORD __stdcall ReceiverThread(LPVOID LParam)
{
	MosyRegistryManager RegistryManager;
	int Port = RegistryManager.Query(MosyValue(L"Port")).GetInteger();
	MosyServerSocket ServerSocket(Port, true);
	MessageBox(NULL, L"ReceiverRun!", L"Run", MB_OK);
	while (1)
	{
		MosySocket sAccept = ServerSocket.Accept();
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (!sAccept.HasConnected())
		{
			printf("accept() Failed:%d\n", WSAGetLastError());
		}
		else
		{
			MosyLogger::Log(MosyValue(L""));
			MosyLogger::Log(MosyValue(sAccept.Receive()));
		}
	}
	return 0;
}

DWORD _stdcall SenderThread(LPVOID LParam)
{

}