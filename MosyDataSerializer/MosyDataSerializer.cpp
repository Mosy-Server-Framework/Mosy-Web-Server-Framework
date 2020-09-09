#include "pch.h"
#include "MosyDataSerializer.h"

void MosyDataSerializer::AddValue(MosyValue Key, MosyValue Value)
{
	wstring nw = L"\"" + Key.GetString() + L"\":\"" + Value.GetString() + L"\",";
	Data += nw;
}

void MosyDataSerializer::AddMap(MosyValue Key, MosyMap Map)
{
	wstring nw = L"\"" + Key.GetString() + L"\":[";
	map<wstring, MosyValue>::iterator it;
	it = Map.begin();
	while (it != Map.end())
	{
		nw += L"\"" + it->first + L"\":\"" + it->second.GetString() + L"\",";
	}
	nw += L"],";
	Data += nw;
}

void MosyDataSerializer::AddArray(MosyValue Key, MosyArray Array)
{
	wstring nw = L"\"" + Key.GetString() + L"\":[";
	vector<MosyValue>::iterator it;
	it = Array.begin();
	while (it != Array.end())
	{
		nw += L"\"" + it->GetString() + L"\",";
	}
	nw += L"],";
	Data += nw;
}

void MosyDataSerializer::AddDataPackage(MosyValue Key, MosyDataPackage Package)
{
	Data += L"\"" + Key.GetString() + L"\":" + Package.Data + L",";
}

void MosyDataSerializer::Clear()
{
	Data = L"";
}

MosyDataPackage MosyDataSerializer::ExportPackage()
{
	MosyDataPackage Export;
	Export.Data = Data;
	return Export;
}
