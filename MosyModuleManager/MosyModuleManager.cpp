#include "pch.h"
#include "MosyModuleManager.h"

void MosyModuleManager::LoadControllerRegistry()
{
	MosyRegistryManager Registry;
	ControllerRegistry = Registry.Query(MosyValue(L"ControllerRegistry"));
	ControllerModulesRegistry = Registry.Query(MosyValue(L"ControllerModulesRegistry"));
	FunctionRegistry = Registry.Query(MosyValue(L"FunctionWrapper"));
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

MosyValue MosyModuleManager::GetFunctionAtModule(MosyValue Name)
{
	wchar_t Ret[MAX_PATH];
	GetPrivateProfileStringW(Name.GetString().c_str(), L"Module", L"__NOT_FOUND__", Ret, MAX_PATH, FunctionRegistry.GetString().c_str());
	MosyValue ModulePath(Ret);
	return ModulePath;
}

MosyModuleManager::MosyModuleManager()
{
	LoadControllerRegistry();
}

RestfulControllerTemplate MosyModuleManager::LoadRestfulController(MosyValue ControllerName)
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
		RestfulControllerTemplate Controller = (RestfulControllerTemplate)GetProcAddress(Instance, MosyString::WString2String(ControllerName.GetString()).c_str());
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

ViewControllerTemplate MosyModuleManager::LoadViewController(MosyValue ControllerName)
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
		ViewControllerTemplate Controller = (ViewControllerTemplate)GetProcAddress(Instance, MosyString::WString2String(ControllerName.GetString()).c_str());
		if (Controller == NULL)
		{
			int Err = GetLastError();
			throw MosyModuleLoader::MosyModuleLoaderException(MosyModuleLoader::MOSY_MODULE_LOADER_FAILED_TO_LOAD_VIEW_CONTROLLER);
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

MosyFunctionTemplate MosyModuleManager::LoadFunction(MosyValue FunctionName)
{
	try
	{
		HINSTANCE Instance;
		MosyValue ModuleName = GetFunctionAtModule(FunctionName);
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
		MosyFunctionTemplate Controller = (MosyFunctionTemplate)GetProcAddress(Instance, MosyString::WString2String(FunctionName.GetString()).c_str());
		if (Controller == NULL)
		{
			int Err = GetLastError();
			throw MosyModuleLoader::MosyModuleLoaderException(MosyModuleLoader::MOSY_MODULE_LOADER_FAILED_TO_LOAD_RESTFUL_CONTROLLER);
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

MosyValue MosyModuleManager::ExecuteRestfulController(MosyValue ControllerName, MosyEnvironment Environment, MosyControllerParams Params)
{
	RestfulControllerTemplate Controller = LoadRestfulController(ControllerName);
	return (*Controller)(Environment,Params);
}

MosyViewModule MosyModuleManager::ExecuteViewController(MosyValue ControllerName, MosyEnvironment Environment, MosyControllerParams Params)
{
	ViewControllerTemplate Controller = LoadViewController(ControllerName);
	return (*Controller)(Environment, Params);
}

MosyFunctionResult MosyModuleManager::ExecuteFunction(MosyValue ControllerName, MosyEnvironment Environment, MosyControllerParams Params)
{
	MosyFunctionTemplate Controller = LoadFunction(ControllerName);
	return (*Controller)(Environment, Params);
}
