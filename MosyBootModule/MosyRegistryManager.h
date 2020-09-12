#pragma once
#include "MosyMap.h"
#include "MosyValue.h"
#include "MosyString.h"
#include <map>
#include <string>
#include "MosyProFileManager.h"
using namespace std;

class _declspec(dllexport) MosyRegistryManager
{
protected:
	map<wstring, map<MosyValue, MosyValue>>Registry;
public:
	MosyValue Query(MosyValue MosyRegistry, MosyValue Key);
	void UpDate();
	MosyRegistryManager();
	~MosyRegistryManager();
};

