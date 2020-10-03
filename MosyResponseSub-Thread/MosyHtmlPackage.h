#pragma once
#include "MosyObject.h"
#include <string>
#include <vector>
#include <iostream>

class _declspec(dllexport) MosyHtmlPackage :
	public MosyObject
{
public:
	long Length;
	std::vector<char> Html;
	std::wstring type;
	bool Exit = true;
	MosyHtmlPackage();
	~MosyHtmlPackage();
};

