#pragma once
#include <map>
#include "MosyValue.h"
#ifdef DLL_FILE
class _declspec(dllexport)
	MosyMap :
	public MosyObject,
	public std::map<std::wstring, MosyObject>
#else
class _declspec(dllimport)
	MosyMap :
	public MosyObject,
	public std::map<std::wstring, MosyValue>
#endif
{
public:
	virtual MosyObject* obj()override;
};

