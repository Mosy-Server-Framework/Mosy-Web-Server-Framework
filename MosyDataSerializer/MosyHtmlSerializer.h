#pragma once
#include "MosyHtmlPackage.h"
#include "MosyString.h"
#include <string>
#define BUF_LENGTH 1024

class _declspec(dllexport) MosyHtmlSerializer
{
public:
	MosyHtmlPackage AddString(std::wstring Context);
	MosyHtmlPackage AddString(std::string Context);
	MosyHtmlPackage AddFile(std::wstring FilePath);
	MosyHtmlPackage AddFile(std::string FilePath);
};

