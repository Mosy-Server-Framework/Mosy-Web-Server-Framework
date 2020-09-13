#pragma once
#include "MosyObject.h"
#include "MosyString.h"
#include <string>
#ifdef DLL_FILE
const class _declspec(dllexport)
MosyValue :
	public MosyObject
#else
const class _declspec(dllimport)
MosyValue :
	public MosyObject
#endif
{
protected:
	std::wstring Value;
public:
	MosyValue();
	MosyValue(std::wstring s);
	MosyValue(double s);
	int GetInteger();
	double GetDouble();
	std::wstring GetString();
	bool GetBoolean();
	virtual MosyObject* obj()override;
};

