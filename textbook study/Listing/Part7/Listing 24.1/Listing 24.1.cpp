#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	if (!DeleteFile("D:\\demo_file.dat"))
	{
		cerr << "Delete file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	cout << "The file is deleted." << endl;

	system("pause");

	return 0;
}