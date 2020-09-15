#pragma once
#include "MosyObject.h"
#include <string>

class _declspec(dllimport) MosyDataPackage:public MosyObject
{
public:
	std::wstring Data;
	MosyDataPackage();
	~MosyDataPackage();
};

