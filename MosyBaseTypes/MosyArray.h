#pragma once
#include <vector>
#include "MosyObject.h"
#include "MosyValue.h"
#ifdef DLL_FILE
class _declspec(dllexport)
	MosyArray :
	public MosyObject,
	public std::vector<MosyObject>
#else
class _declspec(dllexport)
	MosyArray :
	public MosyObject,
	public std::vector<MosyValue>
#endif
{
public:
	virtual MosyObject* obj()override;
};

