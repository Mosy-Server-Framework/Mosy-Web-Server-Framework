#include "pch.h"
#include "Test.h"

extern "C"
{
	MosyRestfulResult TestRest(MosyControllerParams Params)
	{
		return MosyRestfulResult(Params[L"Test"]);
	}
}