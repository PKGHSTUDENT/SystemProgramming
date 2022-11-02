#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hStdOut;
	SMALL_RECT sr;
	
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << "Set new window rectangle in characters." << endl << endl;
	cout << "Input left coordinate (0-79): ";
	cin >> sr.Left;
	
	cout << "Input top coordinate (0-24): ";
	cin >> sr.Top;
	
	cout << "Input right coordinate (0-79): ";
	cin >> sr.Right;
	
	cout << "Input bottom coordinate (0-24): ";
	cin >> sr.Bottom;
	
	if (!SetConsoleWindowInfo(hStdOut, TRUE, &sr))
		cout << "Set console window info failed." << endl;
	
	cin.get();	
	
	system("pause");

	return 0;
}