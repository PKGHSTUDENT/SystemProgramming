#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hInEvent;
CHAR lpEventName[] = "InEventName";

int main()
{
	char c;

	hInEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, lpEventName);

	if (hInEvent == NULL)
	{
		cout << "Open event failed." << endl;
		return GetLastError();
	}

	cout << "Input any char: ";
	cin >> c;

	SetEvent(hInEvent);

	CloseHandle(hInEvent);

	system("pause");

	return 0;
}