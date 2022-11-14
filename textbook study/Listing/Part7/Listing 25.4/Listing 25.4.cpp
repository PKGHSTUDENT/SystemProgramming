#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	if (!RemoveDirectory("D:\\demo_dir"))
	{
		cerr << "Remove directory failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	cout << "The directory is removed." << endl;
	
	system("pause");

	return 0;
}