// ComTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <strsafe.h>
#include "atlbase.h"
#import "..\AutoSvr\Debug\AutoSvr.tlb" no_namespace

using namespace std;

TCHAR szCommand[10];
TCHAR szSvcName[80];
VOID __stdcall DisplayUsage(void);

struct OleCom
{
	OleCom() { CoInitialize(NULL); }
	~OleCom() { CoUninitialize(); }
}olecom;

int _tmain(int argc, _TCHAR* argv[])
{
	CComPtr<IUnknown> spUnknown;
	spUnknown.CoCreateInstance(__uuidof(SvcControlComponent));
	CComPtr<ISvcControl> pI;
	spUnknown.QueryInterface(&pI);

	//spUnknown.QueryInterface(&pI);
	
	if (argc != 3)
	{
		printf("ERROR: Incorrect number of arguments\n\n");
		DisplayUsage();
		return 1;
	}
	StringCchCopy(szCommand, 10, argv[1]);
	StringCchCopy(szSvcName, 80, argv[2]);

	if (lstrcmpi(szCommand, TEXT("start")) == 0)
		pI->DoStartSvc(szSvcName);
	else if (lstrcmpi(szCommand, TEXT("dacl")) == 0)
		pI->DoUpdateSvcDacl(szSvcName);
	else if (lstrcmpi(szCommand, TEXT("stop")) == 0)
		pI->DoStopSvc(szSvcName);
	else
	{
		_tprintf(TEXT("Unknown command (%s)\n\n"), szCommand);
		DisplayUsage();
	}
}

VOID __stdcall DisplayUsage()
{
	printf("Description:\n");
	printf("\tCommand-line tool that controls a service.\n\n");
	printf("Usage:\n");
	printf("\ComTest [command] [service_name]\n\n");
	printf("\t[command]\n");
	printf("\t  start\n");
	printf("\t  dacl\n");
	printf("\t  stop\n");
}