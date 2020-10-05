#include "pch.h"
#include "MosyRequestWrapper.h"

MosyRequestWrapperResult MosyRequestWrapper::GetRequestTarget(MosyValue RequestPath, MosyValue Method)
{
	MosyRegistryManager RegistryManager;
	MosyRequestWrapperResult Result;
	MosyValue WrapperFile = RegistryManager.Query(MosyValue(L"RequestWrapper"));
	wchar_t Type[MAX_PATH];
	GetPrivateProfileStringW(RequestPath.GetString().c_str(), L"Type", L"__NOT_FOUND__", Type, MAX_PATH, WrapperFile.GetString().c_str());
	if (!lstrcmpW(Type, L"__NOT_FOUND__"))
	{
		wstring ResourceWrapper = WrapperFile.GetString().substr(0, WrapperFile.GetString().find_last_of(L"\\"));
		ResourceWrapper += L"\\MosyResourceWrapper.ini";
		int All = GetPrivateProfileIntW(L"Wrapper", L"Count", 0, ResourceWrapper.c_str());
		for (int i = 0; i < All; i++)
		{
			wchar_t Path[MAX_PATH], Index[20];
			wsprintfW(Index, L"%d", i);
			GetPrivateProfileStringW(Index, L"Path", L"__NOT_FOUND__", Path, MAX_PATH, ResourceWrapper.c_str());
			if (RequestPath.GetString().find(Path) == 0)
			{
				wchar_t CPath[MAX_PATH];
				GetPrivateProfileStringW(Path, L"Path", L"__NOT_FOUND__", CPath, MAX_PATH, WrapperFile.GetString().c_str());
				if (!lstrcmpiW(CPath, L"__NOT_FOUND__"))
				{
					Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
					Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:Cannot Find File or Controller,Please Confirm whether the Wrapper Registry is Registered Correctly."));
					return Result;
				}
				else
				{
					wstring Pth = RequestPath.GetString();
					Pth.replace(0,lstrlenW(Path),L"");
					while (Pth.find(L"/") != Pth.npos)
					{
						Pth = Pth.replace(Pth.find(L"/"), 1, L"\\");
					}
					Result.insert_or_assign(L"Type", MosyValue(L"Resource"));
					Result.insert_or_assign(L"Path", MosyValue(wstring(CPath) + Pth.substr(0,Pth.find_last_not_of(L" ") + 1)));
					return Result;
				}
			}
			else
			{
				Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
				Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:Cannot Find File or Controller,Please Confirm whether the Wrapper Registry is Registered Correctly."));
				return Result;
			}
		}
	}
	else
	{
		if (!lstrcmpW(Type, L"RestController"))
		{
			wchar_t Mth[20];
			GetPrivateProfileStringW(RequestPath.GetString().c_str(), L"Method", L"__NOT_FOUND__", Mth, 20, WrapperFile.GetString().c_str());
			if (!lstrcmpW(Mth, L"__NOT_FOUND__"))
			{
				Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
				Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:The Registry Key is Missing, Please Confirm whether the Wrapper Registry is Registered Correctly."));
				return Result;
			}
			if (Method.GetString() != Mth)
			{
				Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
				Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:The Request Method does not Match, Please Confirm that the Request Method is Correct."));
				return Result;
			}
			wchar_t Controller[MAX_PATH];
			GetPrivateProfileStringW(RequestPath.GetString().c_str(), L"Controller", L"__NOT_FOUND__", Controller, MAX_PATH, WrapperFile.GetString().c_str());
			if (!lstrcmpW(Controller, L"__NOT_FOUND__"))
			{
				Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
				Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:The Registry Key is Missing, Please Confirm whether the Wrapper Registry is Registered Correctly."));
				return Result;
			}
			Result.insert_or_assign(L"Type", MosyValue(L"RestController"));
			Result.insert_or_assign(L"Path", MosyValue(wstring(Controller)));
			return Result;
		}
		else if (!lstrcmpW(Type, L"ViewController"))
		{
			wchar_t Mth[20];
			GetPrivateProfileStringW(RequestPath.GetString().c_str(), L"Method", L"__NOT_FOUND__", Mth, 20, WrapperFile.GetString().c_str());
			if (!lstrcmpW(Mth, L"__NOT_FOUND__"))
			{
				Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
				Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:The Registry Key is Missing, Please Confirm whether the Wrapper Registry is Registered Correctly."));
				return Result;
			}
			if (Method.GetString() != Mth)
			{
				Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
				Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:The Request Method does not Match, Please Confirm that the Request Method is Correct."));
				return Result;
			}
			wchar_t Controller[MAX_PATH];
			GetPrivateProfileStringW(RequestPath.GetString().c_str(), L"Controller", L"__NOT_FOUND__", Controller, MAX_PATH, WrapperFile.GetString().c_str());
			if (!lstrcmpW(Controller, L"__NOT_FOUND__"))
			{
				Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
				Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:The Registry Key is Missing, Please Confirm whether the Wrapper Registry is Registered Correctly."));
				return Result;
			}
			Result.insert_or_assign(L"Type", MosyValue(L"ViewController"));
			Result.insert_or_assign(L"Path", MosyValue(wstring(Controller)));
			return Result;
		}
		else
		{
			Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
			Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:Cannot Find File or Controller!"));
			return Result;
		}
	}
	Result.insert_or_assign(L"Type", MosyValue(L"ERROR"));
	Result.insert_or_assign(L"Msg", MosyValue(L"Wrapper Error:Unknow Error."));
	return Result;
}
