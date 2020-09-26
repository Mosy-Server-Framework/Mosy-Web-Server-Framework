#pragma once
#include "MosyHtmlPackage.h"
#include "MosyString.h"
#include <string>
#include <map>
#define BUF_LENGTH 1024
using namespace std;

class _declspec(dllexport) MosyHtmlSerializer
{
protected:
	map<wstring, wstring> FileTypes;
public:
	MosyHtmlPackage AddString(std::wstring Context);
	MosyHtmlPackage AddString(std::string Context);
	MosyHtmlPackage AddFile(std::wstring FilePath);
	MosyHtmlPackage AddFile(std::string FilePath);
	MosyHtmlSerializer();
	~MosyHtmlSerializer();
};

