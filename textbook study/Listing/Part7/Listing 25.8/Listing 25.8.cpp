#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hChangeHandle;

	hChangeHandle = FindFirstChangeNotification(
		"D:\\demo_dir",
		TRUE,
		FILE_NOTIFY_CHANGE_FILE_NAME
		| FILE_NOTIFY_CHANGE_SIZE);

	if (hChangeHandle == INVALID_HANDLE_VALUE)
	{
		cerr << "Find first change notification failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	cout << "Wait for changes in the directory." << endl;
	
	if (WaitForSingleObject(hChangeHandle, INFINITE) == WAIT_OBJECT_0)
		cout << "First notification: the directory was changed." << endl;
	else
	{
		cerr << "Wait for single object failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	if (!FindNextChangeNotification(hChangeHandle))
	{
		cerr << "Find next change notification failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	if (WaitForSingleObject(hChangeHandle, INFINITE) == WAIT_OBJECT_0)
		cout << "Next notification: the directory was changed." << endl;
	else
	{
		cerr << "Wait for single object failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	FindCloseChangeNotification(hChangeHandle);
	
	system("pause");

	return 0;
}