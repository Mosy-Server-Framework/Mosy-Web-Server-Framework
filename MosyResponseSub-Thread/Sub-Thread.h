#pragma once
#include "pch.h"
#include "MosyMessageQueue.h"
#include "MosyRequestPackage.h"
#include "MosyRequestQueuePackage.h"
#include "MosyResponsePackage.h"
#include "MosyResponseQueuePackage.h"
#include "MosySocket.h"
#include "MosyRequestDeserializer.h"
#include "MosyResponseSerializer.h"
#include "MosyDataPackage.h"
#include "MosyHtmlPackage.h"
#include "MosyDataSerializer.h"
#include "MosyHtmlSerializer.h"
#include "ThreadStruct.h"
#include "MosyLogger.h"
#include <string.h>
using namespace std;

DWORD _stdcall SubThread(LPVOID Param);
DWORD _stdcall SenderThread(LPVOID Param);

DWORD _stdcall InitThread(LPVOID Param)
{
	MosySocket Socket;
	//MosyLogger::Log(MosyValue(L"Mosy InitThread Ready"));
	try
	{
		Socket = (((MosyMessageQueue*)Param)->GetRequestSocket());
		wstring ReceiveData = Socket.Receive();
		MosyRequestPackage RequestPackage = MosyRequestDeserializer::Parse(ReceiveData);
		MosyRequestQueuePackage qp;
		qp.Package = RequestPackage;
		qp.ClientSocket = Socket.GetHandler();
		((MosyMessageQueue*)Param)->PushRequestPackage(qp);
		CreateThread(NULL, NULL, SubThread, Param, NULL, NULL);
	}
	catch (MosySocket::MosySocketException* e)
	{
		MosyLogger::Log(MosyValue(MosyString::String2WString(e->what())));
		Socket.Close();
	}
	catch (exception* e)
	{
		MosyLogger::Log(MosyValue(MosyString::String2WString(e->what())));
	}
	//MosyLogger::Log(MosyValue(L"Mosy InitThread Terminal"));
	return 0;
}

DWORD _stdcall SubThread(LPVOID Param)
{
	try
	{
		MosyRequestQueuePackage RequestQueuePackage = ((MosyMessageQueue*)Param)->GetRequestPackage();
		MosyRequestPackage RequestPackage = RequestQueuePackage.Package;
		//MosyLogger::Log(MosyValue(L"Mosy Sub-Thread Ready"));
		MosyHtmlSerializer HtmlSerializer;
		string Path = MosyString::WString2String(RequestPackage.TargetInterface);
		MosyHtmlPackage HtmlPackage = HtmlSerializer.AddFile(Path);
		MosyResponsePackage Response;
		if (HtmlPackage.Exit)
		{
			Response = MosyResponseSerializer::Serialize(MOSY_200, HtmlPackage);
		}
		else
		{
			Response = MosyResponseSerializer::Serialize(MOSY_404, HtmlPackage);
		}
		MosyResponseQueuePackage qp;
		qp.ClientSocket = RequestQueuePackage.ClientSocket;
		qp.Package = Response;
		((MosyMessageQueue*)Param)->PushResponsePackage(qp);
		//MosyLogger::Log(MosyValue(L"Mosy Sub-Thread Terminal"));
		CreateThread(NULL, NULL, SenderThread, Param, NULL, NULL);
	}
	catch (exception* e)
	{
		MosyLogger::Log(MosyValue(MosyString::String2WString(e->what())));
	}
	return 0;
}

DWORD _stdcall SenderThread(LPVOID Param)
{
	MosyResponseQueuePackage ResponseQueuePackage = ((MosyMessageQueue*)Param)->GetResponsePackage();
	MosySocket Socket;
	try
	{
		Socket = ResponseQueuePackage.ClientSocket;
		Socket.Send(ResponseQueuePackage.Package.Head + ResponseQueuePackage.Package.Body);
		Socket.Close();
	}
	catch (MosySocket::MosySocketException* e)
	{
		MosyLogger::Log(MosyValue(MosyString::String2WString(e->what())));
		Socket.Close();
	}
	catch (exception* e)
	{
		MosyLogger::Log(MosyValue(MosyString::String2WString(e->what())));
	}
	return 0;
}