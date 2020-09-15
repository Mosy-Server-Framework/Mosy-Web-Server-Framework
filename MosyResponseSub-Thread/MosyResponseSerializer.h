#pragma once
#include "MosyResponsePackage.h"
#include "MosyDataPackage.h"
#include "MosyHtmlPackage.h"

enum ResponseStatus
{
	MOSY_100,
	MOSY_101,
	MOSY_200,
	MOSY_204,
	MOSY_206,
	MOSY_301,
	MOSY_302,
	MOSY_303,
	MOSY_304,
	MOSY_401,
	MOSY_402,
	MOSY_403,
	MOSY_404,
	MOSY_405,
	MOSY_406,
	MOSY_408,
	MOSY_414,
	MOSY_415,
	MOSY_416,
	MOSY_499,
	MOSY_500,
	MOSY_501,
	MOSY_502,
	MOSY_503,
	MOSY_504,
	MOSY_505,
	MOSY_428,
	MOSY_429,
	MOSY_431,
	MOSY_511,
};
class _declspec(dllexport) MosyResponseSerializer
{
public:
	static MosyResponsePackage Serialize(ResponseStatus Status, MosyDataPackage DataPackage);
	static MosyResponsePackage Serialize(ResponseStatus Status, MosyHtmlPackage DataPackage);
};

