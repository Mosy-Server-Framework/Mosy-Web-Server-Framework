#pragma once

#include "MosyObject.h"
#include "MosyString.h"
#include "MosyValue.h"
#include <map>
#include <vector>
using namespace std;

typedef MosyValue(*RestfulControllerTamplate)(map<wstring, MosyValue>);
typedef map<MosyValue, vector<MosyValue>>(*DataBaseInterface)(MosyValue QueryString);
typedef MosyValue MosyModuleInstance;