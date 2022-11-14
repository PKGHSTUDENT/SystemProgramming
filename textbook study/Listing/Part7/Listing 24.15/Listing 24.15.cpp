#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;
	BY_HANDLE_FILE_INFORMATION bhfi;
	
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
	
	cout << "File attributes: " << bhfi.dwFileAttributes << endl
		<< "Creation time: high date: "
		<< bhfi.ftCreationTime.dwHighDateTime << endl
		<< "Creation time: low date: "
		<< bhfi.ftCreationTime.dwLowDateTime << endl
		<< "Last access time: high date: "
		<< bhfi.ftLastAccessTime.dwHighDateTime << endl
		<< "Last access time: low date: "
		<< bhfi.ftLastAccessTime.dwLowDateTime << endl
		<< "Last write time: high date: "
		<< bhfi.ftLastWriteTime.dwHighDateTime << endl
		<< "Last write time: low date: "
		<< bhfi.ftLastWriteTime.dwLowDateTime << endl
		<< "Volume serial number: " << bhfi.dwVolumeSerialNumber << endl
		<< "File size high: " << bhfi.nFileSizeHigh << endl
		<< "File size low: " << bhfi.nFileSizeLow << endl
		<< "Number of links: " << bhfi.nNumberOfLinks << endl
		<< "File index high: " << bhfi.nFileIndexHigh << endl
		<< "File index low: " << bhfi.nFileIndexLow << endl;
	
	CloseHandle(hFile);
	
	system("pause");

	return 0;
}