#include "pch.h"
#include "MosyProFileManager.h"
#pragma warning(disable:4996)

bool MosyProFileManager::FileExists(wstring FilePath)
{
	wchar_t szExeFilePathFileName[MAX_PATH];
	GetModuleFileNameW(NULL, szExeFilePathFileName, MAX_PATH);
	std::wstring str = szExeFilePathFileName;
	int idx = str.find_last_of('\\');
	std::wstring sss = str.substr(0, idx);
	if (FilePath[0] == L'.')
	{
		FilePath = FilePath.substr(1, FilePath.length());
		FilePath = sss + FilePath;
	}
	string strPath = MosyString::WString2String(FilePath);
	bool ac = false;
	fstream fs;
	fs.open(strPath.c_str(), ios::in);
	if (fs) 
	{
		ac = true;
	}
	else
	{
		ac = false;
	}
	fs.close();
	return ac;
}

wstring MosyProFileManager::GetMosyProfileString(wstring Path, wstring Index1, wstring Index2, wstring Default)
{
	//if (FileExists(Path))
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
	//if (FileExists(Path))
	{
		int d = Default;
		d = GetPrivateProfileIntW(Index1.c_str(), Index2.c_str(), Default, Path.c_str());
		return d;
	}
	return Default;
}

bool MosyProFileManager::GetMosyProfilebool(wstring Path, wstring Index1, wstring Index2, bool Default)
{
	//if (FileExists(Path))
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
