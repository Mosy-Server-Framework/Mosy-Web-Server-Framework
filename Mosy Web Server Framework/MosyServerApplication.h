#pragma once
#include "MosyRegistryManager.h"

class _declspec(dllimport) MosyServerApplication
{
public:
	void static Boot();
	static MosyRegistryManager RegistryManager;
};

