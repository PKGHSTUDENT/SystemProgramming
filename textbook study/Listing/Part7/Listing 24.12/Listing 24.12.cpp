#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;
	
	LARGE_INTEGER liFileSize;

	hFile = CreateFile(
		"D:\\demo_file.dat",
		GENERIC_READ,
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

	if (!GetFileSizeEx(hFile, &liFileSize))
		cerr << "Get file size failed." << endl
		<< "The last error code: " << GetLastError() << endl;

	CloseHandle(hFile);
	
	system("pause");

	return 0;
}