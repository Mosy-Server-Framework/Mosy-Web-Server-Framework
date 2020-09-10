#include "pch.h"
#include "MosyRegistryManager.h"

MosyValue MosyRegistryManager::Query(MosyValue MosyRegistry, MosyValue Key)
{
	return Registry[MosyRegistry.GetString][Key.GetString()];
}

void MosyRegistryManager::UpDate()
{

}
