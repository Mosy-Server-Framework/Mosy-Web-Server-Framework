#include "pch.h"
#include "Test.h"

MosyRestfulResult TestRest(MosyEnvironment Environment, MosyControllerParams Params)
{
	ViewControllerTemplate Controller = ((MosyModuleManager*)Environment[L"ModuleManager"])->LoadViewController(MosyValue(L"TestView"));
	MosyViewModule ViewModule = (*Controller)(Environment, Params);
	return MosyRestfulResult(ViewModule[L"View"]);
}

MosyViewModule TestView(MosyEnvironment Environment, MosyControllerParams Params)
{
	MosyViewModule ViewModule;
	ViewModule.insert_or_assign(L"View", MosyValue(L"/Test/default.html"));
	return ViewModule;
}