#pragma once
#include "MosyObject.h"
#include <string>

class _declspec(dllexport) MosyDataPackage:public MosyObject
{
public:
	std::wstring Data;
	MosyDataPackage();
	~MosyDataPackage();
};

