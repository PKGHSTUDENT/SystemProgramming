#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	if (!MoveFile("D:\\demo_file.dat", "D:\\new.dat"))
	{
		cerr << "Move file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	cout << "The file is moved." << endl;

	system("pause");
	
	return 0;
}