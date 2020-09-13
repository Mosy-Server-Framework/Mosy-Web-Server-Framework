#include "pch.h"
#include "MosyProFileManager.h"

bool MosyProFileManager::FileExists(wstring FilePath)
{
	return _access(MosyString::WString2String(FilePath).c_str(),0);
}

wstring MosyProFileManager::GetMosyProfileString(wstring Path, wstring Index1, wstring Index2, wstring Default)
{
	if (FileExists(Path))
	{
		wstring d;
		d = Default;
		wchar_t Return[MAX_PATH];
		GetPrivateProfileStringW(Index1.c_str(), Index2.c_str(), d.c_str(), Return, MAX_PATH, Path.c_str());
		wstring retv(Return);
		return retv;
	}
	return Default;
}

int MosyProFileManager::GetMosyProfileInt(wstring Path, wstring Index1, wstring Index2, int Default)
{
	if (FileExists(Path))
	{
		int d = Default;
		wchar_t Return[MAX_PATH];
		d = GetPrivateProfileIntW(Index1.c_str(), Index2.c_str(), Default, Path.c_str());
		return d;
	}
	return Default;
}

bool MosyProFileManager::GetMosyProfilebool(wstring Path, wstring Index1, wstring Index2, bool Default)
{
	if (FileExists(Path))
	{
		wstring d;
		if (Default)
		{
			d = L"true";
		}
		else
		{
			d = L"false";
		}
		wchar_t Return[MAX_PATH];
		GetPrivateProfileStringW(Index1.c_str(), Index2.c_str(), d.c_str(), Return, MAX_PATH, Path.c_str());
		wstring retv(Return);
		return retv == L"true";
	}
	return Default;
}
