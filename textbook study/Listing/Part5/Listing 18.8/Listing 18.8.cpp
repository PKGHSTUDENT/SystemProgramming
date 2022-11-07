#include <windows.h>
#include <iostream>
#include <float.h>

#pragma warning(disable : 4996)

using namespace std;


int main()
{
	double a = 0;
	int cw = _controlfp(0, 0);

	cw &= ~(EM_OVERFLOW | EM_UNDERFLOW
		| EM_INEXACT | EM_ZERODIVIDE | EM_DENORMAL);
	
	_controlfp(cw, _MCW_EM);
	
	__try
	{
		double b;
		b = 1 / a;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD ec = GetExceptionCode();

		if (ec == EXCEPTION_FLT_DIVIDE_BY_ZERO)
			cout << "Exception float divide by zero." << endl;
		else
			cout << "Some other exception." << endl;
	}

	system("pause");
	
	return 0;
}