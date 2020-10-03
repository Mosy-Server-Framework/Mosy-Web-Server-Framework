#pragma once
#include <string>
#include <comdef.h>
#include "MosyObject.h"
#ifdef DLL_FILE
const class _declspec(dllexport)
	MosyString
#else
const class _declspec(dllimport)
	MosyString
#endif
{
public:
	static std::string WString2String(std::wstring wstr);
	static std::wstring String2WString(std::string str);
};

