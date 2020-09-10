#pragma once
#include <vector>
#include "MosyObject.h"
#include "MosyValue.h"

class _declspec(dllimport)
	MosyArray :
	public MosyObject,
	public std::vector<MosyValue>
{
public:
	virtual MosyObject* obj()override;
};

