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

	for (int i = 0; i < 5; ++i)
	{
		int nData;
		cin >> nData;
		cout << "The number " << nData << " is read from the pipe." << endl;
	}
	
	SetEvent(hReadFloat);
	
	for (int j = 0; j < 5; ++j)
	{
		Sleep(500);
		cout << (j * 0.1) << endl;
	}
	
	WaitForSingleObject(hReadText, INFINITE);

	cout << "The process read the text: ";
	
	char lpszInput[80];
	
	do
	{
		Sleep(500);
		cin >> lpszInput;
		cout << lpszInput << " ";
	} while (*lpszInput != '\0');

	cout << endl << "The process finished transmission of data." << endl;
	
	CloseHandle(hReadFloat);
	CloseHandle(hReadText);
	
	system("pause");
	
	return 0;
}