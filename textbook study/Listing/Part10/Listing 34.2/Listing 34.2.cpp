#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	char service_name[] = "DemoService";
	const char* param[] = { "p1", "p2", "p3" };

	SC_HANDLE hServiceControlManager, hService;
	
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

	if (!StartService(
		hService,
		3,
		(const char**)param))
	{
		cout << "Start service failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		CloseServiceHandle(hServiceControlManager);
		CloseServiceHandle(hService);
		return 0;
	}
	cout << "The service is started." << endl;

	CloseServiceHandle(hServiceControlManager);
	CloseServiceHandle(hService);
	
	system("pause");

	return 0;
}