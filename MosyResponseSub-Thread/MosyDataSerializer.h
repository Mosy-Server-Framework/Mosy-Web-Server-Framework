#pragma once
#include "MosyArray.h"
#include "MosyString.h"
#include "MosyMap.h"
#include "MosyValue.h"
#include "MosyDataPackage.h"
#include <string>
using namespace std;

class _declspec(dllimport) MosyDataSerializer
{
protected:
	wstring Data;
public:
	void AddValue(MosyValue Key, MosyValue Value);
	void AddMap(MosyValue Key, MosyMap Map);
	void AddArray(MosyValue Key, MosyArray Array);
	void AddDataPackage(MosyValue Key, MosyDataPackage Package);
	void Clear();
	MosyDataPackage ExportPackage();
};

