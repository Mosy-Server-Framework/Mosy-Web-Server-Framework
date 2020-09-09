#pragma once
#include "MosyObject.h"
#include <string>

class _declspec(dllexport) MosyHtmlPackage :
	public MosyObject
{
public:
	std::wstring Html;
	MosyHtmlPackage();
	~MosyHtmlPackage();
};

