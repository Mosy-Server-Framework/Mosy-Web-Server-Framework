#pragma once
#include "MosyLogger.h"
#include "MosyModuleLoader.h"
#include "MosyObject.h"
#include "MosyString.h"
#include "MosyValue.h"
#include <map>
#include <vector>
using namespace std;

typedef MosyValue(*RestfulControllerTamplate)(map<wstring, MosyValue>);
typedef map<wstring,vector<MosyValue>>(*DataBaseInterface)(MosyValue QueryString);
typedef MosyValue MosyModuleInstance;

class _declspec(dllimport) MosyModuleLoader
{
public:
	enum MosyModuleLoaderErrorCode
	{
		MOSY_MODULE_LOADER_FAILED_TO_LOAD_MODULE,
		MOSY_MODULE_LOADER_FAILED_TO_LOAD_RESTFUL_CONTROLLER,
		MOSY_MODULE_LOADER_FAILED_TO_LOAD_DATABASE_INTERFACE,
	};
	struct MosyModuleLoaderException :public exception
	{
		MosyModuleLoaderErrorCode ErrorCode;
		MosyModuleLoaderException(MosyModuleLoaderErrorCode MosyErrorCode)
		{
			ErrorCode = MosyErrorCode;
		}
		const char * what() const throw ()
		{
			switch (ErrorCode)
			{
			case MOSY_MODULE_LOADER_FAILED_TO_LOAD_MODULE:
				return "Failed to Load Module,Make Sure the Path you have Registried is Right.";
				break;
			case MOSY_MODULE_LOADER_FAILED_TO_LOAD_RESTFUL_CONTROLLER:
				return "Failed to Load Restful Controller,Make Sure the Controller Name you have Registried is Right.";
				break;
			case MOSY_MODULE_LOADER_FAILED_TO_LOAD_DATABASE_INTERFACE:
				return "Failed to Load Database Interface,Make Sure the Interface you have Registried is Right.";
				break;
			default:
				return "Failed to Load Module,Unkonw Error.";
				break;
			}
		}
		MosyModuleLoaderErrorCode GetErrorCode()
		{
			return ErrorCode;
		}
	};
	HINSTANCE LoadMosyModule(MosyValue Path);
	RestfulControllerTamplate GetRestfulController(MosyModuleInstance Instance, MosyValue ControllerName);
	DataBaseInterface GetDataBaseInterface(MosyModuleInstance Instance, MosyValue DatabaseInterfaceName);
	void FreeMosyModule(HINSTANCE ModuleInstance);
};

