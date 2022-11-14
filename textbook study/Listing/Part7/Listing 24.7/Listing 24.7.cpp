#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	if (!ReplaceFile(
		"D:\\new_file.dat",
		"D:\\demo_file.dat",
		"D:\\back_file.dat",
		REPLACEFILE_WRITE_THROUGH,
		NULL, NULL))
	{
		cerr << "Replace file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The file is replaced." << endl;
	
	system("pause");

	return 0;
}