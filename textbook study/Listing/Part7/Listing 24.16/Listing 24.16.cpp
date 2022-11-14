#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;
	BY_HANDLE_FILE_INFORMATION bhfi;
	SYSTEMTIME st;
	
	hFile = CreateFile(
		"D:\\demo_file.dat",
		0,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	if (!GetFileInformationByHandle(hFile, &bhfi))
	{
		cerr << "Get file information by handle failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	if (!FileTimeToSystemTime(&(bhfi.ftCreationTime), &st))
	{
		cerr << "File time to system time failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	cout << "File creation time in system format: " << endl
		<< "\tYear: " << st.wYear << endl
		<< "\tMonth: " << st.wMonth << endl
		<< "\tDay of week: " << st.wDayOfWeek << endl
		<< "\tDay: " << st.wDay << endl
		<< "\tHour: " << st.wHour << endl
		<< "\tMinute: " << st.wMinute << endl
		<< "\tSecond: " << st.wSecond << endl
		<< "\tMilliseconds: " << st.wMilliseconds << endl;
	
	CloseHandle(hFile);
	
	system("pause");

	return 0;
}