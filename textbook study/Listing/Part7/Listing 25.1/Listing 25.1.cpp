#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	if (!CreateDirectory("D:\\demo_dir", NULL))
	{
		cerr << "Create directory failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The directory is created." << endl;
	
	system("pause");

	return 0;
}