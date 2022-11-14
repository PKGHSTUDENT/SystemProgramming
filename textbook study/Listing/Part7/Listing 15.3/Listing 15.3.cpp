#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFindFile;
	WIN32_FIND_DATA fd;
	
	hFindFile = FindFirstFile("D:\\demo_dir\\*", &fd);

	if (hFindFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Find first file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The first file name: " << fd.cFileName << endl;
	
	while (FindNextFile(hFindFile, &fd))
		cout << "The next file name: " << fd.cFileName << endl;
	
	FindClose(hFindFile);

	system("pause");

	return 0;
}
