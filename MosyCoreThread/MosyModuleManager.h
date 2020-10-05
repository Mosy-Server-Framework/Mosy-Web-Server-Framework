#pragma once
#include "MosyLogger.h"
#include "MosyModuleLoader.h"
#include "MosyString.h"
#include "MosyValue.h"
#include <map>
using namespace std;

MosyModuleLoader::MosyModuleLoaderErrorCode;
MosyModuleLoader::MosyModuleLoaderException;

class _declspec(dllimport) MosyModuleManager
{
private:
	MosyValue ControllerRegistry;
	MosyValue ControllerModulesRegistry;
	MosyValue FunctionRegistry;
	map<wstring, HINSTANCE> ModuleList;
	map<wstring, MosyValue> ControllerWrapper;
	MosyModuleLoader Loader;
	void LoadControllerRegistry();
	HINSTANCE GetMosyModule(MosyValue ModuleName);
	void UnLoadMosyModuel(MosyValue ModuleName);
	MosyValue GetAtModule(MosyValue Name);
	MosyValue GetFunctionAtModule(MosyValue Name);
public:
	enum MosyModuleErrorCode
	{
		MOSY_MODULE_FAILED_TO_LOAD_MODULE,
		MOSY_MODULE_FAILED_TO_LOAD_RESTFUL_CONTROLLER,
		MOSY_MODULE_FAILED_TO_LOAD_DATABASE_INTERFACE,
		MOSY_MODULE_UNKNOW_ERROR,
	};
	struct MosyModuleException :public exception
	{
		MosyModuleErrorCode ErrorCode;
		MosyModuleException(MosyModuleErrorCode MosyErrorCode)
		{
			ErrorCode = MosyErrorCode;
		}
		const char * what() const throw ()
		{
			switch (ErrorCode)
			{
			case MOSY_MODULE_FAILED_TO_LOAD_MODULE:
				return "MosyModuleManager:Failed to Load Module,Make Sure the Path you have Registried is Right.";
				break;
			case MOSY_MODULE_FAILED_TO_LOAD_RESTFUL_CONTROLLER:
				return "MosyModuleManager:Failed to Load Restful Controller,Make Sure the Controller Name you have Registried is Right.";
				break;
			case MOSY_MODULE_FAILED_TO_LOAD_DATABASE_INTERFACE:
				return "MosyModuleManager:Failed to Load Database Interface,Make Sure the Interface you have Registried is Right.";
				break;
			default:
				return "MosyModuleManager:Failed to Load Module,Unkonw Error.";
				break;
			}
		}
		MosyModuleErrorCode GetErrorCode()
		{
			return ErrorCode;
		}
	};
	MosyModuleManager();
	RestfulControllerTemplate LoadRestfulController(MosyValue ControllerName);
	ViewControllerTemplate LoadViewController(MosyValue ControllerName);
	MosyFunctionTemplate LoadFunction(MosyValue FunctionName);
	MosyValue ExecuteRestfulController(MosyValue ControllerName, MosyEnvironment Environment, MosyControllerParams Params);
	MosyViewModule ExecuteViewController(MosyValue ControllerName, MosyEnvironment Environment, MosyControllerParams Params);
	MosyFunctionResult ExecuteFunction(MosyValue ControllerName, MosyEnvironment Environment, MosyControllerParams Params);
};

