#pragma once
#include "MosyObject.h"
#include "MosyString.h"
#include "MosyMap.h"
#include <string>

enum METHOD
{
	MOSY_GET,
	MOSY_POST,
	MOSY_PUT,
	MOSY_PATCH,
	MOSY_DELETE,
	MOSY_COPY,
	MOSY_HEAD,
	MOSY_OPTIONS,
	MOSY_LINK,
	MOSY_UNLINK,
	MOSY_PURGE,
	MOSY_LOCK,
	MOSY_UNLOCK,
	MOSY_PROPFIND,
	MOSY_VIEW
};
#ifdef DLL_FILE
class _declspec(dllexport)
	MosyRequestPackage :
	public MosyObject
#else
class _declspec(dllexport)
	MosyRequestPackage :
	public MosyObject
#endif
{
public:
	MosyValue Method;
	std::wstring TargetInterface;
	MosyMap Params;
	MosyRequestPackage();
	~MosyRequestPackage();
	void operator=(MosyRequestPackage p);
};

