// Знакомство работы с WIN32 
// Работа с потоками
#include <iostream>
#include <thread>
#include <string>
#include <process.h>
#include <Windows.h>
using namespace std;

volatile int n;

DWORD WINAPI Add(LPVOID iNum){
    cout << "Thread is started." << endl;
    n += (int)iNum;
    cout << "Thread is finished." << endl;

    return 0;
}

UINT WINAPI thread(void* pString)
{
    int i = 1;
    char* pLexema;
    pLexema = strtok((char*)pString, " ");

    while (pLexema != NULL)
    {
        cout << "Thread find the lexema " << i << " : " << pLexema << endl;
        pLexema = strtok(NULL, " ");
        i++;
    }
}

int main()
{
    int inc = 10;
    HANDLE hThread;
    DWORD IDThread;

    cout << "n = " << n << endl;
    // Запускаем поток Add
    hThread = CreateThread(NULL, 0, Add, (void*)inc, 0, &IDThread);
    if (hThread == NULL)
        return GetLastError();

    // Ждём, пока поток Add закончит работу
    WaitForSingleObject(hThread, INFINITE);

    // Закрываем дескриптор потока Add
    CloseHandle(hThread);

    cout << "n = " << n << endl;


    
    return 0;
}
