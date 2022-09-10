#include <Windows.h>
#include <iostream>

int count;

void main()
{
	for(;;)
	{
		count++;
		Sleep(1000);
		std::cout << "cout = " << count << std::endl;
	}
}