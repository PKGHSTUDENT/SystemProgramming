#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD file_attr;

	file_attr = GetFileAttributes("D:\\demo_file.dat");

	cout << file_attr << endl;

	if (file_attr == -1)
	{
		cerr << "Get file attributes failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	if (file_attr == FILE_ATTRIBUTE_NORMAL)
		cout << "This is a normal file." << endl;
	else
	{
		cout << "This is a not normal file." << endl;
		system("pause");
		return 0;
	}
	
	if (!SetFileAttributes("D:\\demo_file.dat", FILE_ATTRIBUTE_HIDDEN))
	{
		cerr << "Set file attributes failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	cout << "Now the file is hidden." << endl
		<< "Press any key to continue.";
	cin.get();
	
	if (!SetFileAttributes("D:\\demo_file.dat", FILE_ATTRIBUTE_NORMAL))
	{
		cerr << "Set file attributes failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "Now the file is again normal." << endl;

	system("pause");

	return 0;
}