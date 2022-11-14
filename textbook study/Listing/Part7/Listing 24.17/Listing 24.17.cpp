#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;
	DWORD dwFileType;

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
	
	dwFileType = GetFileType(hFile);
	
	switch (dwFileType)
	{
	case FILE_TYPE_UNKNOWN:
		cout << "Unknown type file." << endl;
		break;
	case FILE_TYPE_DISK:
		cout << "Disk type file." << endl;
		break;
	case FILE_TYPE_CHAR:
		cout << "Char type file." << endl;
		break;
	case FILE_TYPE_PIPE:
		cout << "Pipe type file." << endl;
		break;
	default:
		break;
	}

	system("pause");
	return 0;
}