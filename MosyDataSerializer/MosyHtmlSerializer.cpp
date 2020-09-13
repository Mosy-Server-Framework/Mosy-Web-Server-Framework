#include "pch.h"
#include "MosyHtmlSerializer.h"
#pragma warning(disable:4996)

MosyHtmlPackage MosyHtmlSerializer::AddString(std::wstring Context)
{
	MosyHtmlPackage Package;
	Package.Html = Context;
	return Package;
}

MosyHtmlPackage MosyHtmlSerializer::AddString(std::string Context)
{
	MosyHtmlPackage Package;
	Package.Html = MosyString::String2WString(Context);
	return Package;
}

MosyHtmlPackage MosyHtmlSerializer::AddFile(std::wstring FilePath)
{
	MosyHtmlPackage Package;
	FILE *resource = fopen(MosyString::WString2String(FilePath).c_str(), "rb");
	if (resource == NULL)
	{
		return MosyHtmlPackage();
	}
	fseek(resource, 0, SEEK_SET);
	fseek(resource, 0, SEEK_END);
	long flen = ftell(resource);
	fseek(resource, 0, SEEK_SET);
	char send_buf[BUF_LENGTH];
	while (1)
	{
		memset(send_buf, 0, sizeof(send_buf));
		fgets(send_buf, sizeof(send_buf), resource);
		Package.Html += MosyString::String2WString(send_buf);
		if (feof(resource))
			break;
	}
	return Package;
}

MosyHtmlPackage MosyHtmlSerializer::AddFile(std::string FilePath)
{
	MosyHtmlPackage Package;
	FILE *resource = fopen(FilePath.c_str(), "rb");
	if (resource == NULL)
	{
		return MosyHtmlPackage();
	}
	fseek(resource, 0, SEEK_SET);
	fseek(resource, 0, SEEK_END);
	long flen = ftell(resource);
	fseek(resource, 0, SEEK_SET);
	char send_buf[BUF_LENGTH];
	while (1)
	{
		memset(send_buf, 0, sizeof(send_buf));
		fgets(send_buf, sizeof(send_buf), resource);
		Package.Html += MosyString::String2WString(send_buf);
		if (feof(resource))
			break;
	}
	return Package;
}
