#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	char c;
	int* p = NULL;

	cout << "Input 'y' to allocate memory: ";
	cin >> c;

	if (c == 'y')
		p = new int;
	__try
	{
		*p = 10;
	}
	__finally
	{
		delete p;
		cout << "The finally block finished." << endl;
	}

	system("pause");

	return 0;
}
