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

DWORD __stdcall ReceiverThread(LPVOID LParam)
{
	MosyServerSocket ServerSocket();
}