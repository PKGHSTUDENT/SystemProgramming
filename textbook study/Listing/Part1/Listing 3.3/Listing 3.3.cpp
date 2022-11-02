#include <iostream>
#include <Windows.h>

// https://learn.microsoft.com/ru-ru/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminatethread
// https://learn.microsoft.com/ru-ru/windows/win32/procthread/terminating-a-thread

using namespace std;

volatile UINT _count;

void thread()
{
    for (;;)
    {
        ++_count;
        Sleep(100);
    }
}

int main()
{
    HANDLE hThread;
    DWORD IDThread;
    char c;
    _count = 1;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IDThread);

    if (hThread == NULL)
        return GetLastError();

    for (;;)
    {
        cout << "Input 'y' to display the count or any char to finish: ";
        cin >> c;
        if (c == 'y')
            cout << "count = " << _count << endl;
        else
            break;
    }

    TerminateThread(hThread, 0);

    CloseHandle(hThread);

    system("pause");

    return 0;
}
