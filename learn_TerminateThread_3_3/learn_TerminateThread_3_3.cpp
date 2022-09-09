// learn_TerminateThread_3_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

// using namespace std;

volatile UINT count;

void thread()
{
    for (;;)
    {
        ++count;
        Sleep(100);
        // 100 миллисекунд
        // 1000 - 1 секунда
    }
}

int main()
{
    HANDLE hThread;
    DWORD IDThread;
    char c;
    count = 1;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IDThread);
    // LPTHREAD_START_ROUTINE - Points to a function that notifies the host that a thread has started to execute.
    // Указывает на функцию, которая уведомляет хост о начале выполнения потока.
    // Этот указатель функции устарел в .NET Framework 4.

    if (hThread == NULL)
        return GetLastError();

    for (;;)
    {
        std::cout << "Input 'y' to display the count or any char to finish: ";
        std::cin >> c;
        if (c == 'y')
            std::cout << "count = " << count << std::endl;
        else
            break;
    }

    TerminateThread(hThread, 0);
    // Предупреждение	C6258	Использование TerminateThread не позволит выполнить правильную очистку потока.
    
    CloseHandle(hThread);
    return 0;
}
