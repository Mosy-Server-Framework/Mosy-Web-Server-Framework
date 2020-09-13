#pragma once
#include "MosyLogger.h"
#include "MosyRegistryManager.h"
#include "MosyThreadManager.h"
#include "MosyCoreThread.h"
#include "MosyGobalManager.h"

class _declspec(dllexport) MosyServerApplication
{
public:
	void static Boot();
	static MosyRegistryManager RegistryManager;
};

