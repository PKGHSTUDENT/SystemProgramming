﻿#include <iostream>
#include <thread>
#include <string>
#include <process.h>
#include <Windows.h>
using namespace std;

volatile int n;

DWORD WINAPI Add(LPVOID iNum) {
    cout << "Thread is started." << endl;
    n += (int)iNum;
    cout << "Thread is finished." << endl;

    return 0;
}

int main()
{
    int inc = 10;
    HANDLE hThread;
    DWORD IDThread;

    cout << "n = " << n << endl;
    hThread = CreateThread(NULL, 0, Add, (void*)inc, 0, &IDThread);
    if (hThread == NULL)
        return GetLastError();

    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);

    cout << "n = " << n << endl;

    system("pause");

    return 0;
}
