#include <windows.h>
#include <iostream>

#pragma warning(disable : 4996)

using namespace std;

int main(int argc, char* argv[])
{
	char c;
	char answer[] = "This is an answer.";
	
	HANDLE hWrite, hRead;
	char WriteEvent[] = "WriteEvent";
	char ReadEvent[] = "ReadEvent";
	char* v;
	
	hWrite = OpenEvent(EVENT_MODIFY_STATE, FALSE, WriteEvent);
	hRead = OpenEvent(EVENT_MODIFY_STATE, FALSE, ReadEvent);
	
	v = (char*)atoi(argv[1]);
	
	cout << v << endl;
	
	WaitForSingleObject(hWrite, INFINITE);
	strcpy(v, "This is an answer.");
	SetEvent(hRead);
	
	CloseHandle(hWrite);
	CloseHandle(hRead);
	
	system("pause");

	return 0;
}