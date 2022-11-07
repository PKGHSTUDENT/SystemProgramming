#include <windows.h>
#include <iostream>

using namespace std;

LONG new_filter(PEXCEPTION_POINTERS pExceptionInfo)
{
	cout << "New filter-function is called." << endl;
	cout << "Exception code = " << hex
		<< pExceptionInfo->ExceptionRecord->ExceptionCode << endl;

	return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
	int* p = NULL;

	LPTOP_LEVEL_EXCEPTION_FILTER old_filter;

	old_filter =
		SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)new_filter);

	cout << "Old filter-function address = " << hex << old_filter << endl;

	*p = 10;

	system("pause");

	return 0;
}