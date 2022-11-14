#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	if (!CreateDirectoryEx("D:\\demo_dir", "D:\\demo_dir\\demo_subdir", NULL))
	{
		cerr << "Create directory failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The subdirectory is created." << endl;

	system("pause");

	return 0;
}