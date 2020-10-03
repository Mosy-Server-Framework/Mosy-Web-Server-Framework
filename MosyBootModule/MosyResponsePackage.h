#pragma once
#include "MosyObject.h"
#include "string"
#include <vector>
#include <iostream>

class  _declspec(dllimport) MosyResponsePackage :public MosyObject
{
public:
	std::wstring Head;
	std::vector<char> Body;
	int Size;
	MosyResponsePackage();
	~MosyResponsePackage();
};

