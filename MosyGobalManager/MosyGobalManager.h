#pragma once
#include "MosyRegistryManager.h"
#include "MosyThreadManager.h"

class _declspec(dllexport) MosyGobalManager
{
public:
	static MosyRegistryManager RegistryManager;
	static MosyThreadManager ThreadManager;
};

