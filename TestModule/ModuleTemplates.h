#pragma once

#include "MosyObject.h"
#include "MosyString.h"
#include "MosyValue.h"
#include <map>
#include <vector>
using namespace std;

typedef MosyValue(*RestfulControllerTamplate)(map<wstring, MosyValue>);
typedef map<wstring, vector<MosyValue>>(*DataBaseInterface)(MosyValue QueryString);
typedef MosyValue MosyModuleInstance;
typedef MosyValue MosyRestfulResult;
typedef map<wstring, MosyValue> MosyControllerParams;
typedef map<wstring, vector<MosyValue>> DataBaseInterfaceResult;