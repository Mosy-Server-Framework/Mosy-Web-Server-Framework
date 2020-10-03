#include "pch.h"
#include "MosyRequestPackage.h"
#ifndef DLL_FILE
#define DLL_FILE
#endif

MosyRequestPackage::MosyRequestPackage()
{
}

MosyRequestPackage::~MosyRequestPackage()
{
	MosyMap().swap(Params);
}

void MosyRequestPackage::operator=(MosyRequestPackage p)
{
	Params = p.Params;
	TargetInterface = p.TargetInterface;
	Method = p.Method;
}
