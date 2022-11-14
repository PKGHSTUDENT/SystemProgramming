#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	if (!MoveFile("D:\\demo_dir", "D:\\new_dir"))
	{
		cerr << "Move file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The directory is moved." << endl;

	system("pause");
	return 0;
}