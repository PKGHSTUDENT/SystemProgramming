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
		if (!AbnormalTermination())
		{
			delete p;
			cout << "The memory is free." << endl;
		}
		else
			cout << "The memory was not allocated." << endl;
	}

	system("pause");
	return 0;
}