#include "pch.h"
#include "MosyModuleLoader.h"

HINSTANCE MosyModuleLoader::LoadMosyModule(MosyValue Path)
{
	if (Path.GetString()[0] != L'\\')
	{
		Path = L"\\" + Path.GetString();
	}
	Path = L".\\MosyModules" + Path.GetString();
	HINSTANCE Library = LoadLibraryW(Path.GetString().c_str());
	long long int LibId = (long long int)(void*)Library;
	if (Library == NULL)
	{
		throw MosyModuleLoaderException(MOSY_MODULE_LOADER_FAILED_TO_LOAD_MODULE);
		return NULL;
	}
	wchar_t strs[40];
	wsprintfW(strs, L"%I64d", Library);
	return Library;
}

RestfulControllerTemplate MosyModuleLoader::GetRestfulController(MosyModuleInstance Instance, MosyValue ControllerName)
{
	RestfulControllerTemplate Controller = (RestfulControllerTemplate)GetProcAddress((HINSTANCE)Instance.GetLLInteger(), MosyString::WString2String(ControllerName.GetString()).c_str());
	if (Controller == NULL)
	{
		throw MosyModuleLoaderException(MOSY_MODULE_LOADER_FAILED_TO_LOAD_RESTFUL_CONTROLLER);
		return NULL;
	}
	return Controller;
}

ViewControllerTemplate MosyModuleLoader::GetViewController(MosyModuleInstance Instance, MosyValue ControllerName)
{
	ViewControllerTemplate Controller = (ViewControllerTemplate)GetProcAddress((HINSTANCE)Instance.GetLLInteger(), MosyString::WString2String(ControllerName.GetString()).c_str());
	if (Controller == NULL)
	{
		throw MosyModuleLoaderException(MOSY_MODULE_LOADER_FAILED_TO_LOAD_VIEW_CONTROLLER);
		return NULL;
	}
	return Controller;
}

MosyFunctionTemplate MosyModuleLoader::GetFunction(MosyModuleInstance Instance, MosyValue DatabaseInterfaceName)
{
	MosyFunctionTemplate Function = (MosyFunctionTemplate)GetProcAddress((HINSTANCE)Instance.GetLLInteger(), MosyString::WString2String(DatabaseInterfaceName.GetString()).c_str());
	if (Function == NULL)
	{
		throw MosyModuleLoaderException(MOSY_MODULE_LOADER_FAILED_TO_LOAD_RESTFUL_CONTROLLER);
		return NULL;
	}
	return Function;
}

void MosyModuleLoader::FreeMosyModule(HINSTANCE ModuleInstance)
{
	FreeLibrary(ModuleInstance);
}
