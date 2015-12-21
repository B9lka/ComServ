// AutoSvr.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "AutoSvr_i.h"


using namespace ATL;


class CAutoSvrModule : public ATL::CAtlExeModuleT< CAutoSvrModule >
{
public :
	DECLARE_LIBID(LIBID_AutoSvrLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_AUTOSVR, "{64ECD378-D2D9-4AB0-B70E-BA284672707D}")
	};

CAutoSvrModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

