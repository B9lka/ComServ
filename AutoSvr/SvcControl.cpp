// SvcControl.cpp : Implementation of CSvcControl

#include "stdafx.h"
#include "SvcControl.h"

// CSvcControl

STDMETHODIMP CSvcControl::DoStartSvc(LPCWSTR szSvcName, BSTR	*result)
{
	SERVICE_STATUS_PROCESS ssStatus;
	DWORD dwOldCheckPoint;
	DWORD dwStartTickCount;
	DWORD dwWaitTime;
	DWORD dwBytesNeeded;

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // servicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		//printf("OpenSCManager failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("OpenSCManager failed \n"), NULL , MB_OK);
		return S_FALSE;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,         // SCM database 
		szSvcName,            // name of service 
		SERVICE_ALL_ACCESS);  // full access 

	if (schService == NULL)
	{
		//printf("OpenService failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("OpenService failed \n"), NULL, MB_OK);
		CloseServiceHandle(schSCManager);
		return S_FALSE;
	}

	// Check the status in case the service is not stopped. 

	if (!QueryServiceStatusEx(
		schService,                     // handle to service 
		SC_STATUS_PROCESS_INFO,         // information level
		(LPBYTE)&ssStatus,             // address of structure
		sizeof(SERVICE_STATUS_PROCESS), // size of structure
		&dwBytesNeeded))              // size needed if buffer is too small
	{
		//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("QueryServiceStatusEx failed \n"), NULL, MB_OK);
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return S_FALSE;
	}

	// Check if the service is already running. It would be possible 
	// to stop the service here, but for simplicity this example just returns. 

	if (ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
	{
		//printf("Cannot start the service because it is already running\n");
		MessageBox(NULL, _T("Cannot start the service because it is already running\n"), NULL, MB_OK);
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return S_FALSE;
	}

	// Save the tick count and initial checkpoint.

	dwStartTickCount = GetTickCount();
	dwOldCheckPoint = ssStatus.dwCheckPoint;

	// Wait for the service to stop before attempting to start it.

	while (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
	{
		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth of the wait hint but not less than 1 second  
		// and not more than 10 seconds. 

		dwWaitTime = ssStatus.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		// Check the status until the service is no longer stop pending. 

		if (!QueryServiceStatusEx(
			schService,                     // handle to service 
			SC_STATUS_PROCESS_INFO,         // information level
			(LPBYTE)&ssStatus,             // address of structure
			sizeof(SERVICE_STATUS_PROCESS), // size of structure
			&dwBytesNeeded))              // size needed if buffer is too small
		{
			//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			MessageBox(NULL, _T("QueryServiceStatusEx failed\n"), NULL, MB_OK);
			CloseServiceHandle(schService);
			CloseServiceHandle(schSCManager);
			return S_FALSE;
		}

		if (ssStatus.dwCheckPoint > dwOldCheckPoint)
		{
			// Continue to wait and check.

			dwStartTickCount = GetTickCount();
			dwOldCheckPoint = ssStatus.dwCheckPoint;
		}
		else
		{
			if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
			{
				//printf("Timeout waiting for service to stop\n");
				MessageBox(NULL, _T("Timeout waiting for service to stop\n"), NULL, MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return S_FALSE;
			}
		}
	}

	// Attempt to start the service.

	if (!StartService(
		schService,  // handle to service 
		0,           // number of arguments 
		NULL))      // no arguments 
	{
		//printf("StartService failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("StartService failed\n"), NULL, MB_OK);
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return S_FALSE;
	}
	else
	{
		//MessageBox(NULL, _T("Service start pending...\n"), szSvcName, MB_OK);
		//printf("Service start pending...\n");
	}

	// Check the status until the service is no longer start pending. 

	if (!QueryServiceStatusEx(
		schService,                     // handle to service 
		SC_STATUS_PROCESS_INFO,         // info level
		(LPBYTE)&ssStatus,             // address of structure
		sizeof(SERVICE_STATUS_PROCESS), // size of structure
		&dwBytesNeeded))              // if buffer too small
	{
		//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("QueryServiceStatusEx failed\n"), NULL, MB_OK);
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return S_FALSE;
	}

	// Save the tick count and initial checkpoint.

	dwStartTickCount = GetTickCount();
	dwOldCheckPoint = ssStatus.dwCheckPoint;

	while (ssStatus.dwCurrentState == SERVICE_START_PENDING)
	{
		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth the wait hint, but no less than 1 second and no 
		// more than 10 seconds. 

		dwWaitTime = ssStatus.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		// Check the status again. 

		if (!QueryServiceStatusEx(
			schService,             // handle to service 
			SC_STATUS_PROCESS_INFO, // info level
			(LPBYTE)&ssStatus,             // address of structure
			sizeof(SERVICE_STATUS_PROCESS), // size of structure
			&dwBytesNeeded))              // if buffer too small
		{
			//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			MessageBox(NULL, _T("QueryServiceStatusEx failed\n"), NULL, MB_OK);
			break;
		}

		if (ssStatus.dwCheckPoint > dwOldCheckPoint)
		{
			// Continue to wait and check.

			dwStartTickCount = GetTickCount();
			dwOldCheckPoint = ssStatus.dwCheckPoint;
		}
		else
		{
			if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
			{
				// No progress made within the wait hint.
				break;
			}
		}
	}

	// Determine whether the service is running.

	if (ssStatus.dwCurrentState == SERVICE_RUNNING)
	{
		MessageBox(NULL, _T("Service started successfully.\n"), szSvcName, MB_OK);
	}
	else
	{
		printf("Service not started. \n");
		printf("  Current State: %d\n", ssStatus.dwCurrentState);
		printf("  Exit Code: %d\n", ssStatus.dwWin32ExitCode);
		printf("  Check Point: %d\n", ssStatus.dwCheckPoint);
		printf("  Wait Hint: %d\n", ssStatus.dwWaitHint);

	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
	return S_OK;
}

STDMETHODIMP CSvcControl::DoStopSvc(LPCWSTR szSvcName, BSTR * result)
{
	SERVICE_STATUS_PROCESS ssp;
	DWORD dwStartTime = GetTickCount();
	DWORD dwBytesNeeded;
	DWORD dwTimeout = 30000; // 30-second time-out
	DWORD dwWaitTime;

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		//printf("OpenSCManager failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("OpenSCManager failed\n"), NULL, MB_OK);
		return S_FALSE;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,         // SCM database 
		szSvcName,            // name of service 
		SERVICE_STOP |
		SERVICE_QUERY_STATUS |
		SERVICE_ENUMERATE_DEPENDENTS);

	if (schService == NULL)
	{
		//printf("OpenService failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("OpenService failed\n"), NULL, MB_OK);
		CloseServiceHandle(schSCManager);
		return S_FALSE;
	}

	// Make sure the service is not already stopped.

	if (!QueryServiceStatusEx(
		schService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&ssp,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded))
	{
		//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("QueryServiceStatusEx failed\n"), NULL, MB_OK);
		goto stop_cleanup;
	}

	if (ssp.dwCurrentState == SERVICE_STOPPED)
	{
		//printf("Service is already stopped.\n");
		MessageBox(NULL, _T("Service is already stopped.\n"), NULL, MB_OK);
		goto stop_cleanup;
	}

	// If a stop is pending, wait for it.

	while (ssp.dwCurrentState == SERVICE_STOP_PENDING)
	{
		//printf("Service stop pending...\n");
		//MessageBox(NULL, _T("Service stop pending...\n"), NULL, MB_OK);


		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth of the wait hint but not less than 1 second  
		// and not more than 10 seconds. 

		dwWaitTime = ssp.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		if (!QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded))
		{

			//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			MessageBox(NULL, _T("QueryServiceStatusEx failed\n"), NULL, MB_OK);
			goto stop_cleanup;
		}

		if (ssp.dwCurrentState == SERVICE_STOPPED)
		{
			//printf("Service stopped successfully.\n");
			MessageBox(NULL, _T("Service stopped successfully.\n"), szSvcName, MB_OK);
			goto stop_cleanup;
		}

		if (GetTickCount() - dwStartTime > dwTimeout)
		{
			//printf("Service stop timed out.\n");
			MessageBox(NULL, _T("Service stop timed out.\n"), NULL, MB_OK);
			goto stop_cleanup;
		}
	}

	// If the service is running, dependencies must be stopped first.

	StopDependentServices();

	// Send a stop code to the service.

	if (!ControlService(
		schService,
		SERVICE_CONTROL_STOP,
		(LPSERVICE_STATUS)&ssp))
	{
		//printf("ControlService failed (%d)\n", GetLastError());
		MessageBox(NULL, _T("ControlService failed\n"), NULL, MB_OK);
		goto stop_cleanup;
	}

	// Wait for the service to stop.

	while (ssp.dwCurrentState != SERVICE_STOPPED)
	{
		Sleep(ssp.dwWaitHint);
		if (!QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded))
		{
			//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			MessageBox(NULL, _T("QueryServiceStatusEx failed\n"), NULL, MB_OK);
			goto stop_cleanup;
		}

		if (ssp.dwCurrentState == SERVICE_STOPPED)
			break;

		if (GetTickCount() - dwStartTime > dwTimeout)
		{
			//printf("Wait timed out\n");
			MessageBox(NULL, _T("Wait timed out\n"), NULL, MB_OK);
			goto stop_cleanup;
		}
	}
	//printf("Service stopped successfully\n");
	MessageBox(NULL, _T("Service stopped successfully\n"), szSvcName, MB_OK);
	return S_OK;

stop_cleanup:
	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
	return S_FALSE;
}

BOOL CSvcControl::StopDependentServices(void)
{
	DWORD i;
	DWORD dwBytesNeeded;
	DWORD dwCount;

	LPENUM_SERVICE_STATUS   lpDependencies = NULL;
	ENUM_SERVICE_STATUS     ess;
	SC_HANDLE               hDepService;
	SERVICE_STATUS_PROCESS  ssp;

	DWORD dwStartTime = GetTickCount();
	DWORD dwTimeout = 30000; // 30-second time-out

							 // Pass a zero-length buffer to get the required buffer size.
	if (EnumDependentServices(schService, SERVICE_ACTIVE,
		lpDependencies, 0, &dwBytesNeeded, &dwCount))
	{
		// If the Enum call succeeds, then there are no dependent
		// services, so do nothing.
		return TRUE;
	}
	else
	{
		if (GetLastError() != ERROR_MORE_DATA)
			return FALSE; // Unexpected error

						  // Allocate a buffer for the dependencies.
		lpDependencies = (LPENUM_SERVICE_STATUS)HeapAlloc(
			GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded);

		if (!lpDependencies)
			return FALSE;

		__try {
			// Enumerate the dependencies.
			if (!EnumDependentServices(schService, SERVICE_ACTIVE,
				lpDependencies, dwBytesNeeded, &dwBytesNeeded,
				&dwCount))
				return FALSE;

			for (i = 0; i < dwCount; i++)
			{
				ess = *(lpDependencies + i);
				// Open the service.
				hDepService = OpenService(schSCManager,
					ess.lpServiceName,
					SERVICE_STOP | SERVICE_QUERY_STATUS);

				if (!hDepService)
					return FALSE;

				__try {
					// Send a stop code.
					if (!ControlService(hDepService,
						SERVICE_CONTROL_STOP,
						(LPSERVICE_STATUS)&ssp))
						return FALSE;

					// Wait for the service to stop.
					while (ssp.dwCurrentState != SERVICE_STOPPED)
					{
						Sleep(ssp.dwWaitHint);
						if (!QueryServiceStatusEx(
							hDepService,
							SC_STATUS_PROCESS_INFO,
							(LPBYTE)&ssp,
							sizeof(SERVICE_STATUS_PROCESS),
							&dwBytesNeeded))
							return FALSE;

						if (ssp.dwCurrentState == SERVICE_STOPPED)
							break;

						if (GetTickCount() - dwStartTime > dwTimeout)
							return FALSE;
					}
				}
				__finally
				{
					// Always release the service handle.
					CloseServiceHandle(hDepService);
				}
			}
		}
		__finally
		{
			// Always free the enumeration buffer.
			HeapFree(GetProcessHeap(), 0, lpDependencies);
		}
	}
	return TRUE;
}