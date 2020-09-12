#pragma once
#include "MosyLogger.h"
#include "MosyRegistryManager.h"

class _declspec(dllexport) MosyServerApplication
{
public:
	void static Boot();
	static MosyRegistryManager RegistryManager;
};

