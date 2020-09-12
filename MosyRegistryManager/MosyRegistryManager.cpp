#include "pch.h"
#include "MosyRegistryManager.h"

MosyValue MosyRegistryManager::Query(MosyValue MosyRegistry, MosyValue Key)
{
	return Registry[MosyRegistry.GetString()][Key.GetString()];
}

void MosyRegistryManager::UpDate()
{
	map<MosyValue, MosyValue> Temp;
	int Port = MosyProFileManager::GetMosyProfileInt(MOSY_CORE_PROFILE_PATH, L"LocalServer", L"Port", 80);
	bool Debug = MosyProFileManager::GetMosyProfilebool(MOSY_CORE_PROFILE_PATH, L"LocalServer", L"DebugMode", false);
	Temp.insert(pair<MosyValue, MosyValue>(MosyValue(L"Port"), MosyValue(Port)));
	Temp.insert(pair<MosyValue, MosyValue>(MosyValue(L"DebugMode"), MosyValue(Debug)));
	Registry.insert(pair<wstring, map<MosyValue, MosyValue>>(L"LocalServer", Temp));
	Temp.clear();
	wstring ControllerRegistry = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"Registry", L"ControllerRegistry", MOSY_DEFAULT_CONTROLLER_REGISTRY_PATH);
	wstring ControllerInfo = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"Registry", L"ControllerInfo", MOSY_DEFAULT_CONTROLLER_INFO_PATH);
	Temp.insert(pair<MosyValue, MosyValue>(MosyValue(L"ControllerRegistry"), MosyValue(ControllerRegistry)));
	Temp.insert(pair<MosyValue, MosyValue>(MosyValue(L"ControllerInfo"), MosyValue(ControllerInfo)));
	Registry.insert(pair<wstring, map<MosyValue, MosyValue>>(L"Registry", Temp));
	wstring ps[] = { L"ModuleIntegrityCheck",L"ModuleIntegrityCheckDelay",L"ModuleHashCheckWhenIntegrityCheck",L"ModuleBackup",L"ModuleBackupNode",L"ModuleBackupDelay",L"ModuleBackupOverwrite",L"ConfigBackup",L"ConfigBackupNode",L"ConfigBackupDelay",L"ConfigBackupOverwrite",L"ThreadResponseTimeout" };
	Temp.clear();
	for (int i = 0; i < 12; i++)
	{
		wstring t;
		t = MosyProFileManager::GetMosyProfileString(MOSY_CORE_PROFILE_PATH, L"Security", ps[i], L"");
		Temp.insert(pair<MosyValue, MosyValue>(MosyValue(ps[i]), MosyValue(t)));
	}
	Registry.insert(pair<wstring, map<MosyValue, MosyValue>>(L"Security", Temp));
}

MosyRegistryManager::MosyRegistryManager()
{
	UpDate();
}

MosyRegistryManager::~MosyRegistryManager()
{
}
