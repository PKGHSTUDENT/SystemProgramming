#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	int* p = NULL;

	__try
	{
		cout << "a = " << *p << endl;
	}
	__except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
		EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "Exception access violation." << endl;
		p = &a;
	}

	cout << "a = " << *p << endl;
	
	system("pause");
	
	return 0;
}