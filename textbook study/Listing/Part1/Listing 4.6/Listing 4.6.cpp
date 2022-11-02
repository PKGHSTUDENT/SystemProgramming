#include <windows.h>
#include <iostream>

using namespace std;

int _count;
void main()
{
	for (; ; )
	{
		_count++;
		Sleep(1000);
		cout << "count = " << _count << endl;
	}
}