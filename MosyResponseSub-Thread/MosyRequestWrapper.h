#pragma once
#include "MosyValue.h"
#include "MosyString.h"
#include "MosyLogger.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

typedef map<wstring, MosyValue> MosyRequestWrapperResult;
class _declspec(dllexport) MosyRequestWrapper
{
public:
	static MosyRequestWrapperResult GetRequestTarget(MosyValue RequestPath, MosyValue Method);
};

