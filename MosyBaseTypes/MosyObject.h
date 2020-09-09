#pragma once
#include <string>
#ifdef DLL_FILE
class _declspec(dllexport)
	MosyObject
#else
class _declspec(dllexport)
	MosyObject
#endif
{
public:
	MosyObject();
	~MosyObject();
	virtual MosyObject* obj();
};

