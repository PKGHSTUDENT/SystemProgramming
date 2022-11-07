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
	int* p = NULL;
	__try
	{
		*p = 10;
	}
	__except (filter_function(GetExceptionInformation()))
	{
		cout << "ExceptionCode = " << er.ExceptionCode << endl;
		cout << "ExceptionFlags = " << er.ExceptionFlags << endl;
		cout << "ExceptionRecord = " << er.ExceptionRecord << endl;
		cout << "ExceptionAddress = " << er.ExceptionAddress << endl;
		cout << "NumberParameters = " << er.NumberParameters << endl;
	
		if (er.ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
		{
			cout << "Type of access = " << er.ExceptionInformation[0]
				<< endl;
			cout << "Address of access = " << er.ExceptionInformation[1]
				<< endl;
		}
		cout << endl;
	}

	system("pause");

	return 0;
}