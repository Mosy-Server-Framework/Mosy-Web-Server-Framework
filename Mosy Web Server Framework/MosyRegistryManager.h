#pragma once
#include "MosyValue.h"
#include "MosyString.h"
#include <map>
#include <string>
using namespace std;
typedef  map<wstring, MosyValue> MosyRegistry;
typedef  pair<wstring, MosyValue> MosyRegistryPair;

class _declspec(dllimport) MosyRegistryManager
{
protected:
	MosyRegistry Registry;
public:
	MosyValue Query(MosyValue Key);
	void UpDate();
	MosyRegistryManager();
	~MosyRegistryManager();
};

