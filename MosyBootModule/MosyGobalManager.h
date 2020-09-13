#pragma once
#include "MosyRegistryManager.h"
#include "MosyThreadManager.h"

class _declspec(dllimport) MosyGobalManager
{
public:
	static MosyRegistryManager RegistryManager;
	static MosyThreadManager ThreadManager;
};

