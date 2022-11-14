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
	{ NULL, NULL }
	};
	if (!StartServiceCtrlDispatcher(service_table))
	{
		out.open("D:\\ServiceFile.log");
		out << "Start service control dispatcher failed.";
		out.close();
		return 0;
	}
	return 0;
}