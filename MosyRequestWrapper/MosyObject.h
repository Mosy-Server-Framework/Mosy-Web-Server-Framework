#pragma once
#include <string>
#ifdef DLL_FILE
class _declspec(dllimport)
	MosyObject
#else
class _declspec(dllimport)
	MosyObject
#endif
{
public:
	MosyObject();
	~MosyObject();
	virtual MosyObject* obj();
};

