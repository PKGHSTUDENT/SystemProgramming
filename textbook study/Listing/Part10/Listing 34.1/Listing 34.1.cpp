#include <windows.h>
#include <iostream>

using namespace std;

// https://stackoverflow.com/questions/39326284/cant-query-run-or-stop-a-windows-service
// https://learn.microsoft.com/ru-ru/windows/win32/services/service-security-and-access-rights?redirectedfrom=MSDN

int main()
{
	SC_HANDLE hServiceControlManager, hService;
	
	hServiceControlManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_CREATE_SERVICE);

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

	hService = CreateService(
		hServiceControlManager,
		"DemoService",
		"Demo_Service",
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		"D:\\Listing 31.1.exe",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);

	if (hService == NULL)
	{
		cout << "Create service failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		CloseServiceHandle(hServiceControlManager);
		return 0;
	}
	cout << "Service is installed." << endl;
	
	CloseServiceHandle(hService);
	CloseServiceHandle(hServiceControlManager);
	
	system("pause");

	return 0;
}