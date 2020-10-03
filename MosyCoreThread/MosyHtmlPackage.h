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
	MosyHtmlPackage();
	~MosyHtmlPackage();
};

