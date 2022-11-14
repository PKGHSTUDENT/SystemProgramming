#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD dwBinaryType;

	if (!GetBinaryType("D:\\Listing 24.17.exe", &dwBinaryType))
	{
		cerr << "Get binary type failed." << endl
			<< "The file may not be executable." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	if (dwBinaryType == SCS_32BIT_BINARY)
		cout << "The file is Win32 based application." << endl;
	else
		cout << "The file is not Win32 based application." << endl;

	system("pause");

	return 0;
}