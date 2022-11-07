#include <windows.h>
#include <iostream>

using namespace std;

EXCEPTION_RECORD er;

DWORD filter_function(EXCEPTION_POINTERS* p)
{
	er = *(p->ExceptionRecord);
	return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
	int a = 10;
	int b = 20;

	// DWORD Arguments[2];
	ULONG_PTR Arguments[2];

	__try
	{
		if (a < b)
		{
			Arguments[0] = a;
			Arguments[1] = b;

			RaiseException(0xFF, 0, 2, Arguments);
		}
		else
		{
			cout << "There is no any exception." << endl;
			cout << "a - b = " << (a - b) << endl;
		}
	}
	__except (filter_function(GetExceptionInformation()))
	{
		cout << "There is an exception." << endl;

		if (er.ExceptionCode == 0xFF)
		{
			cout << "Exception code = " << hex << er.ExceptionCode << endl;
			cout << "Number parameters = " << dec << er.NumberParameters
				<< endl;
			cout << "Parameter[0] = " << er.ExceptionInformation[0] << endl;
			cout << "Parameter[1] = " << er.ExceptionInformation[1] << endl;
		}
	}

	system("pause");
	return 0;
}