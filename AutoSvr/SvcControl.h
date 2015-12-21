// SvcControl.h : Declaration of the CSvcControl

#pragma once
#include "resource.h"       // main symbols
#include <aclapi.h>


#include "AutoSvr_i.h"
/*
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>
*/

#pragma comment(lib, "advapi32.lib")

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CSvcControl

class ATL_NO_VTABLE CSvcControl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSvcControl, &CLSID_SvcControlComponent>,
	public IDispatchImpl<ISvcControl, &IID_ISvcControl, &LIBID_AutoSvrLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSvcControl()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_SVCCONTROL)
	
	
	BEGIN_COM_MAP(CSvcControl)
		COM_INTERFACE_ENTRY(ISvcControl)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
private:
	TCHAR szCommand[10];
	TCHAR szSvcName[80];
	SC_HANDLE schSCManager;
	SC_HANDLE schService;

public:
	STDMETHOD(DoStartSvc)(BSTR* result);
	STDMETHOD(DoUpdateSvcDacl)(BSTR* result);
	STDMETHOD(DoStopSvc)(BSTR* result);
	BOOL __stdcall StopDependentServices(void);

};

OBJECT_ENTRY_AUTO(__uuidof(SvcControlComponent), CSvcControl)
