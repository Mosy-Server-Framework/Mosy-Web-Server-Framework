#pragma once
#include "MosyObject.h"
#include <string>

class _declspec(dllexport) MosyHtmlPackage :
	public MosyObject
{
public:
	long Length;
	std::wstring Html;
	MosyHtmlPackage();
	~MosyHtmlPackage();
};

