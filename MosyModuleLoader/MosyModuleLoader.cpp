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

RestfulControllerTamplate MosyModuleLoader::GetRestfulController(MosyModuleInstance Instance, MosyValue ControllerName)
{
	RestfulControllerTamplate Controller = (RestfulControllerTamplate)GetProcAddress((HINSTANCE)Instance.GetLLInteger(), MosyString::WString2String(ControllerName.GetString()).c_str());
	if (Controller == NULL)
	{
		throw MosyModuleLoaderException(MOSY_MODULE_LOADER_FAILED_TO_LOAD_RESTFUL_CONTROLLER);
		return NULL;
	}
	return Controller;
}

DataBaseInterface MosyModuleLoader::GetDataBaseInterface(MosyModuleInstance Instance, MosyValue DatabaseInterfaceName)
{
	DataBaseInterface DbInterface = (DataBaseInterface)GetProcAddress((HINSTANCE)Instance.GetLLInteger(), MosyString::WString2String(DatabaseInterfaceName.GetString()).c_str());
	if (DbInterface == NULL)
	{
		throw MosyModuleLoaderException(MOSY_MODULE_LOADER_FAILED_TO_LOAD_RESTFUL_CONTROLLER);
		return NULL;
	}
	return DbInterface;
}

void MosyModuleLoader::FreeMosyModule(HINSTANCE ModuleInstance)
{
	FreeLibrary(ModuleInstance);
}
