#include <windows.h>
#include <fstream>

using namespace std;

char service_name[] = "DemoService";

SERVICE_STATUS service_status;
SERVICE_STATUS_HANDLE hServiceStatus;

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
VOID WINAPI ServiceCtrlHandler(DWORD dwControl);

ofstream out;
int nCount;

int main()
{
	SERVICE_TABLE_ENTRY service_table[] =
	{
	{service_name, ServiceMain},
	{ NULL, NULL }};

	if (!StartServiceCtrlDispatcher(service_table))
	{
		out.open("D:\\ServiceFile.log");
		out << "Start service control dispatcher failed. Error number: " << GetLastError() << endl;
		out.close();
		return 0;
	}
	system("pause");
	return 0;
}

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	hServiceStatus = RegisterServiceCtrlHandler(
		service_name,
		ServiceCtrlHandler);

	if (!hServiceStatus)
	{
		out.open("D:\\ServiceFile.log");
		out << "Register service control handler failed.";
		out.close();
		return;
	}

	service_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	service_status.dwCurrentState = SERVICE_START_PENDING;
	service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP |
		SERVICE_ACCEPT_SHUTDOWN;
	service_status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
	service_status.dwServiceSpecificExitCode = 0;
	service_status.dwCheckPoint = 0;
	service_status.dwWaitHint = 5000;

	if (!SetServiceStatus(hServiceStatus, &service_status))
	{
		out.open("D:\\ServiceFile.log");
		out << "Set service status 'SERVICE_START_PENDING' failed.";
		out.close();
		return;
	}

	service_status.dwCurrentState = SERVICE_RUNNING;

	service_status.dwWin32ExitCode = NO_ERROR;

	if (!SetServiceStatus(hServiceStatus, &service_status))
	{
		out.open("D:\\ServiceFile.log");
		out << "Set service status 'START_PENDING' failed.";
		out.close();
		return;
	}

	out.open("D:\\ServiceFile.log");
	out << "The service is started." << endl << flush;
	out << "My name is: " << lpszArgv[0] << endl << flush;

	for (int i = 1; i < (int)dwArgc; ++i)
		out << "My " << i << " parameter = " << lpszArgv[i] << endl << flush;

	while (service_status.dwCurrentState == SERVICE_RUNNING)
	{
		++nCount;
		Sleep(3000);
	}
}

VOID WINAPI ServiceCtrlHandler(DWORD dwControl)
{
	switch (dwControl)
	{
	case SERVICE_CONTROL_STOP:

		out << "Count = " << nCount << endl;
		out << "The service is finished." << endl << flush;
		out.close();

		service_status.dwCurrentState = SERVICE_STOPPED;

		SetServiceStatus(hServiceStatus, &service_status);
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		service_status.dwCurrentState = SERVICE_STOPPED;

		SetServiceStatus(hServiceStatus, &service_status);
		break;
	default:
		++service_status.dwCheckPoint;
		SetServiceStatus(hServiceStatus, &service_status);
		break;
	}
	return;
}