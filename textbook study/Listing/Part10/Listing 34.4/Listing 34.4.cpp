#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	char service_name[] = "DemoService"; 

	SC_HANDLE hServiceControlManager, hService;
	QUERY_SERVICE_CONFIG* lpQueryServiceConfig;
	DWORD dwBytesNeeded;
	
	hServiceControlManager = OpenSCManager(
		NULL, 
		NULL, 
		SC_MANAGER_CONNECT);

	if (hServiceControlManager == NULL)
	{
		cout << "Open service control manager failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	cout << "Service control manager is opened." << endl
		<< "Press any key to continue." << endl;
	cin.get();
	
	hService = OpenService(
		hServiceControlManager, 
		service_name, 
		SERVICE_ALL_ACCESS 
	);
	if (hService == NULL)
	{
		cout << "Open service failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		CloseServiceHandle(hServiceControlManager);
		return 0;
	}

	cout << "Service is opened." << endl;
	system("pause");
	
	lpQueryServiceConfig = (LPQUERY_SERVICE_CONFIG)new char[4096];
	
	if (!QueryServiceConfig(
		hService, 
		lpQueryServiceConfig, 
		4096, 
		&dwBytesNeeded))
	{
		cout << "Query service configuartion failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		CloseServiceHandle(hServiceControlManager);
		CloseServiceHandle(hService);
		return 0;
	}
	
	cout << "Service type: " << lpQueryServiceConfig->dwServiceType << endl
		<< "Start type: " << lpQueryServiceConfig->dwStartType << endl
		<< "Error control: " << lpQueryServiceConfig->dwErrorControl << endl
		<< "Binary path name: " << lpQueryServiceConfig->lpBinaryPathName
		<< endl
		<< "Service start name: " << lpQueryServiceConfig->lpServiceStartName
		<< endl
		<< "Display name: " << lpQueryServiceConfig->lpDisplayName << endl
		<< endl;
	
	delete[] lpQueryServiceConfig;
	
	CloseServiceHandle(hServiceControlManager);
	CloseServiceHandle(hService);

	system("pause");

	return 0;
}