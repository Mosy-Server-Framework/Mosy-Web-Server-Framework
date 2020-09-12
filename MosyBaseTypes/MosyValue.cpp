#include "pch.h"
#include "MosyValue.h"
#ifndef DLL_FILE
#define DLL_FILE
#endif
MosyValue::MosyValue()
{
}
MosyValue::MosyValue(std::wstring s)
{
	Value = s;
}
MosyValue::MosyValue(double s)
{
	wchar_t str[1000];
	wsprintfW(str, L"%lf", s);
	Value = str;
}

int MosyValue::GetInteger()
{
	return atoi(MosyString::WString2String(Value).c_str());
}

double MosyValue::GetDouble()
{
	return atof(MosyString::WString2String(Value).c_str());
}

std::wstring MosyValue::GetString()
{
	return Value;
}

bool MosyValue::GetBoolean()
{
	if (GetInteger() != 0)
	{
		return true;
	}
	return false;
}

MosyObject * MosyValue::obj()
{
	return this;
}
