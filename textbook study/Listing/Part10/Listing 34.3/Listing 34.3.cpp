#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	char service_name[] = "DemoService";

	SC_HANDLE hServiceControlManager, hService;
	SERVICE_STATUS service_status;

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
		SERVICE_ALL_ACCESS);

	if (hService == NULL)
	{
		cout << "Open service failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		CloseServiceHandle(hServiceControlManager);
		return 0;
	}

	cout << "Service is opened." << endl
		<< "Press any key to continue." << endl;
	cin.get();

	if (!QueryServiceStatus(
		hService,
		&service_status))
	{
		cout << "Query service sataus failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		CloseServiceHandle(hServiceControlManager);
		CloseServiceHandle(hService);
		return 0;
	}

	switch (service_status.dwCurrentState)
	{
	case SERVICE_STOPPED:
		cout << "The service is stopped." << endl;
		break;
	case SERVICE_RUNNING:
		cout << "The service is running." << endl;
		break;
	default:
		cout << "The service status: " << service_status.dwCurrentState
			<< endl;
		break;
	}

	CloseServiceHandle(hServiceControlManager);
	CloseServiceHandle(hService);

	system("pause");

	return 0;
}