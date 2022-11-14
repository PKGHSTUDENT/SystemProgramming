#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	if (!CopyFile("D:\\demo_file.dat", "D:\\new_file.dat", FALSE))
	{
		cerr << "Copy file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The file is copied." << endl;
	
	system("pause");

	return 0;
}