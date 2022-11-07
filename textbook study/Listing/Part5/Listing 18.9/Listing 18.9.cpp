#include <windows.h>
#include <iostream>

using namespace std;

void f(int* p)
{
	int a = 10;
	*p = a;
}

void g(int* p)
{
	int a = 0;
	*p /= a;
}

int main()
{
	int a = 10;
	int* p = NULL;

	__try
	{
		__try
		{
			f(p);
		}
		__except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
		{
			cout << "Exception access violation." << endl;
		}

		p = &a;
		
		__try
		{
			g(p);
		}
		__except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
		{
			cout << "Exception access violation." << endl;
		}
	}
	__except (GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ?
		EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "Exception integer divide by zero." << endl;
	}

	system("pause");

	return 0;
}