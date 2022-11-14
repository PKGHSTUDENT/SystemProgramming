#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD dwNumberOfChar;
	char szDirName[MAX_PATH];

	dwNumberOfChar = GetCurrentDirectory(MAX_PATH, szDirName);

	if (dwNumberOfChar == 0)
	{
		cerr << "Get current directory failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "Current directory name: " << szDirName << endl;

	if (!SetCurrentDirectory("D:\\demo_dir"))
	{
		cerr << "Set current directory failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	dwNumberOfChar = GetCurrentDirectory(MAX_PATH, szDirName);

	if (dwNumberOfChar == 0)
	{
		cerr << "Get current directory failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "Current directory name: " << szDirName << endl;

	system("pause");

	return 0;
}