#pragma once
#include "MosyObject.h"
#include <string>

class _declspec(dllexport) MosyHtmlPackage :
	public MosyObject
{
public:
	long Length;
	std::wstring Html;
	std::wstring type;
	bool Exit = true;
	MosyHtmlPackage();
	~MosyHtmlPackage();
};

