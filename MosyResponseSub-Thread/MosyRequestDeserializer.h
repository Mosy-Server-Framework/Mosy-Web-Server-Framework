#pragma once
#include "MosyRequestPackage.h"
#include "MosyValue.h"
#include <string>
#ifdef DLL_FILE
class _declspec(dllexport)
	MosyRequestPatcher
#else
class _declspec(dllexport)
	MosyRequestDeserializer
#endif
{
public:
	static MosyRequestPackage Parse(std::wstring str);
	static MosyRequestPackage Parse(std::string str);
};

