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
	
	cout << "Input right coordinate (" << (sr.Left - 79) << ','
		<< sr.Left << "): ";
	cin >> sr.Right;
	
	cout << "Input bottom coordinate (" << (sr.Top - 24) << ','
		<< sr.Top << "): ";
	cin >> sr.Bottom;
	
	if (!SetConsoleWindowInfo(hStdOut, FALSE, &sr))
		cout << "Set console window info failed." << endl;
	cin.get();
	
	system("pause");

	return 0;
}