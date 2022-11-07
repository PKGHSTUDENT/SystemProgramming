#include <windows.h>
#include <iostream>
#include <eh.h>

using namespace std;

void se_trans_func(unsigned code, EXCEPTION_POINTERS * info)
{
	EXCEPTION_RECORD er;
	CONTEXT c;
	EXCEPTION_POINTERS ep = { &er, &c };
	
	er = *(info->ExceptionRecord);
	c = *(info->ContextRecord);
	
	throw ep;
}

int main()
{
	int a = 10, b = 0;
	
	_set_se_translator(se_trans_func);
	
	try
	{
		a /= b;
	}
	catch (EXCEPTION_POINTERS ep)
	{
		cout << "Exception code = " << hex
			<< ep.ExceptionRecord->ExceptionCode << endl;
	}

	system("pause");
	return 0;
}