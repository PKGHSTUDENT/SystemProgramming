#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	int* p = NULL;

	__try
	{
		if (!p)
		{
			cout << "Exit with goto from the try block." << endl;
			goto exit_try;
		}
		else
			*p = 10;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cout << "There was some exception." << endl;
	}

	cout << "*p = " << *p << endl;

	system("pause");

exit_try: return 0;
}