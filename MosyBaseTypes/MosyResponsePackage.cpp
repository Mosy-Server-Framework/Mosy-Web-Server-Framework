#include "pch.h"
#include "MosyResponsePackage.h"

MosyResponsePackage::MosyResponsePackage()
{
}

MosyResponsePackage::~MosyResponsePackage()
{
	std::vector<char>().swap(Body);
}
