#include "pch.h"
#include "MosyObject.h"
#ifndef DLL_FILE
#define DLL_FILE
#endif

MosyObject::~MosyObject()
{
}

MosyObject * MosyObject::obj()
{
	return this;
}

MosyObject::MosyObject()
{
}
