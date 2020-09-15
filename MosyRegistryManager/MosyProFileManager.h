#pragma once
#include "MosyString.h"
#include <string>
#ifdef WIN32
#include <io.h> 
#include <fstream>                   //C (Windows)    access
#else
#include <unistd.h>                  //C (Linux)      access   
#endif
using namespace std;
#define MOSY_CORE_PROFILE_PATH L".\\MosyConfig\\Config.ini"
#define MOSY_DEFAULT_CONTROLLER_REGISTRY_PATH L".\\MosyConfig\\MosyControllerRegistry.ini"
#define MOSY_DEFAULT_CONTROLLER_INFO_PATH L".\\MosyConfig\\MosyControllerInfo.ini"

class MosyProFileManager
{
protected:
	bool static FileExists(wstring FilePath);
public:
	static wstring GetMosyProfileString(wstring Path, wstring Index1, wstring Index2, wstring Default);
	static int GetMosyProfileInt(wstring Path, wstring Index1, wstring Index2, int Default);
	static bool GetMosyProfilebool(wstring Path, wstring Index1, wstring Index2, bool Default);
};

