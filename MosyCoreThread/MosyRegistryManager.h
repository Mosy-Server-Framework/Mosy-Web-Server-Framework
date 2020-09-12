#pragma once
#include "MosyMap.h"
#include "MosyValue.h"
#include "MosyString.h"
#include <map>
#include <string>
using namespace std;

class _declspec(dllimport) MosyRegistryManager
{
protected:
	map<wstring, map<MosyValue, MosyValue>>Registry;
public:
	MosyValue Query(MosyValue MosyRegistry, MosyValue Key);
	void UpDate();
	MosyRegistryManager();
	~MosyRegistryManager();
};

