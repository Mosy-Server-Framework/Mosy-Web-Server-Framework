#include "pch.h"
#include "MosyModuleManager.h"

void MosyModuleManager::LoadControllerRegistry()
{
	MosyRegistryManager Registry;
	ControllerRegistry = Registry.Query(MosyValue(L"ControllerRegistry"));
	ControllerModulesRegistry = Registry.Query(MosyValue(L"ControllerModulesRegistry"));
}

HINSTANCE MosyModuleManager::GetMosyModule(MosyValue ModuleName)
{
	if (ModuleList.count(ModuleName.GetString()) == 0)
	{
		wchar_t Ret[MAX_PATH];
		GetPrivateProfileStringW(ModuleName.GetString().c_str(), L"Path", L"__NOT_FOUND__", Ret, MAX_PATH, ControllerModulesRegistry.GetString().c_str());
		MosyValue ModulePath(Ret);
		HINSTANCE Instance = Loader.LoadMosyModule(ModulePath);
		ModuleList.insert_or_assign(ModuleName.GetString(), Instance);
		return Instance;
	}
	else
	{
		return ModuleList[ModuleName.GetString()];
	}
}

void MosyModuleManager::UnLoadMosyModuel(MosyValue ModuleName)
{
	if (ModuleList.count(ModuleName.GetString()) != 0)
	{
		HINSTANCE Instance = ModuleList[ModuleName.GetString()];
		Loader.FreeMosyModule(Instance);
	}
}

MosyValue MosyModuleManager::GetAtModule(MosyValue Name)
{
	wchar_t Ret[MAX_PATH];
	GetPrivateProfileStringW(Name.GetString().c_str(), L"Module", L"__NOT_FOUND__", Ret, MAX_PATH, ControllerRegistry.GetString().c_str());
	MosyValue ModulePath(Ret);
	return ModulePath;
}

MosyModuleManager::MosyModuleManager()
{
	LoadControllerRegistry();
}

RestfulControllerTamplate MosyModuleManager::LoadRestfulController(MosyValue ControllerName)
{
	try
	{
		HINSTANCE Instance;
		MosyValue ModuleName = GetAtModule(ControllerName);
		if (ModuleList.count(ModuleName.GetString()) == 0)
		{
			wchar_t Ret[MAX_PATH];
			GetPrivateProfileStringW(ModuleName.GetString().c_str(), L"Path", L"__NOT_FOUND__", Ret, MAX_PATH, ControllerModulesRegistry.GetString().c_str());
			MosyValue ModulePath(Ret);
			Instance = LoadLibraryW(ModulePath.GetString().c_str());
			ModuleList.insert_or_assign(ModuleName.GetString(), Instance);
		}
		else
		{
			Instance = ModuleList[ModuleName.GetString()];
		}
		RestfulControllerTamplate Controller = (RestfulControllerTamplate)GetProcAddress(Instance, "TestRest");
		if (Controller == NULL)
		{
			int Err = GetLastError();
			throw MosyModuleLoader::MosyModuleLoaderException(MosyModuleLoader:: MOSY_MODULE_LOADER_FAILED_TO_LOAD_RESTFUL_CONTROLLER);
			return NULL;
		}
		return Controller;
	}
	catch (MosyModuleLoader::MosyModuleLoaderException e)
	{
		MosyLogger::Log(MosyValue(L"Mosy Module Manager Error:" + MosyString::String2WString(e.what())));
		throw MosyModuleException((MosyModuleErrorCode)e.ErrorCode);
		return NULL;
	}
	catch (exception e)
	{
		MosyLogger::Log(MosyValue(L"Mosy Module Manager Error:Unknow Error!"));
		throw MosyModuleException(MosyModuleManager::MOSY_MODULE_UNKNOW_ERROR);
		return NULL;
	}
}

DataBaseInterface MosyModuleManager::LoadDataBaseInterface(MosyValue InterfaceName)
{
	try
	{
		HINSTANCE Instance = GetMosyModule(GetAtModule(InterfaceName));
		return NULL;
	}
	catch (MosyModuleLoader::MosyModuleLoaderException e)
	{
		MosyLogger::Log(MosyValue(L"Mosy Module Manager Error:" + MosyString::String2WString(e.what())));
		throw MosyModuleException((MosyModuleErrorCode)e.ErrorCode);
		return NULL;
	}
	catch (exception e)
	{
		MosyLogger::Log(MosyValue(L"Mosy Module Manager Error:Unknow Error!"));
		throw MosyModuleException(MosyModuleManager::MOSY_MODULE_UNKNOW_ERROR);
		return NULL;
	}
}
