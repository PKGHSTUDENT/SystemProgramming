#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hReadFloat, hReadText;

	char lpszReadFloat[] = "ReadFloat";
	char lpszReadText[] = "ReadText";

	hReadFloat = CreateEvent(NULL, FALSE, FALSE, lpszReadFloat);
	hReadText = CreateEvent(NULL, FALSE, FALSE, lpszReadText);
	
	system("pause");

	for (int i = 0; i < 5; ++i)
	{
		Sleep(500);
		cout << i << endl;
	}

	WaitForSingleObject(hReadFloat, INFINITE);
	
	for (int j = 0; j < 5; ++j)
	{
		float nData;
		cin >> nData;
		cout << "The number " << nData << " is read from the pipe." << endl;
	}

	SetEvent(hReadText);
	
	cout << "This is a demo sentence." << endl;
	
	cout << '\0' << endl;

	cout << "The process finished transmission of data." << endl;
	
	CloseHandle(hReadFloat);
	CloseHandle(hReadText);
	
	system("pause");
	
	return 0;
}