#pragma once
#include "MosyObject.h"
#include "MosyString.h"
#include "MosyValue.h"
#include <string>
#include <ctime>
using namespace std;

class _declspec(dllexport) MosyLogger
{
protected:
	static wstring GenHead();
public:
	static void BootLogo();
	static void Log(MosyValue Text);
};

