#include "pch.h"
#include "MosyRegistryManager.h"

MosyValue MosyRegistryManager::Query(MosyValue Key)
{
	return Registry[Key.GetString()];
}

void MosyRegistryManager::UpDate()
{
	wstring Port = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"LocalServer", L"Port", L"80");
	wstring Debug = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"LocalServer", L"DebugMode", L"false");
	Registry.insert(MosyRegistryPair(L"Port", MosyValue(Port)));
	Registry.insert(MosyRegistryPair(L"DebugMode", MosyValue(Debug)));
	wstring ControllerRegistry = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"Register", L"ControllerRegistry", MOSY_DEFAULT_CONTROLLER_REGISTRY_PATH);
	wstring ControllerInfo = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"Register", L"ControllerModulesRegistry", MOSY_DEFAULT_CONTROLLER_INFO_PATH);
	wstring RequestWrapper = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"Register", L"RequestWrapper", MOSY_DEFAULT_REQUEST_WRAPPER_PATH);
	wstring FunctionWrapper = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"Register", L"FunctionWrapper", MOSY_DEFAULT_FUNCTION_WRAPPER_PATH);
	Registry.insert(MosyRegistryPair(L"ControllerRegistry", MosyValue(ControllerRegistry)));
	Registry.insert(MosyRegistryPair(L"ControllerModulesRegistry", MosyValue(ControllerInfo)));
	Registry.insert(MosyRegistryPair(L"RequestWrapper", MosyValue(RequestWrapper)));
	Registry.insert(MosyRegistryPair(L"FunctionWrapper", MosyValue(FunctionWrapper)));
	wstring ps[] = { L"ModuleIntegrityCheck",L"ModuleIntegrityCheckDelay",L"ModuleHashCheckWhenIntegrityCheck",L"ModuleBackup",L"ModuleBackupNode",L"ModuleBackupDelay",L"ModuleBackupOverwrite",L"ConfigBackup",L"ConfigBackupNode",L"ConfigBackupDelay",L"ConfigBackupOverwrite",L"ThreadResponseTimeout" };
	for (int i = 0; i < 12; i++)
	{
		wstring t;
		t = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"Security", ps[i], L"");
		Registry.insert(MosyRegistryPair(ps[i], MosyValue(t)));
	}
}

MosyRegistryManager::MosyRegistryManager()
{
	wchar_t szExeFilePathFileName[MAX_PATH];
	GetModuleFileNameW(NULL, szExeFilePathFileName, MAX_PATH);
	std::wstring str = szExeFilePathFileName;
	int idx = str.find_last_of('\\');
	std::wstring sss = str.substr(0, idx);
	SetCurrentDirectoryW(sss.c_str());
	UpDate();
}

MosyRegistryManager::~MosyRegistryManager()
{
}
