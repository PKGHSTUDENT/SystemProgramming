// Создание потока макрокомандой _beginthreadex
//

#include <Windows.h>
#include <iostream>
#include <string>
#include <process.h>

#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)

using namespace std;

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
	return 0;
}

int main()
{
	char sentence[80];
	int i, j, k = 0;
	HANDLE hThread;
	UINT IDThread;

	cout << "Input string: ";
	cin.getline(sentence, 80);
	j = strlen(sentence);

	hThread = (HANDLE)
		_beginthreadex(NULL, 0, thread, sentence, 0, &IDThread);
	// lpThreadAttributes - NULL / атрибуты защиты / ос сама выставляет сама параметры защиты
	// dwStackSize - 0 / размер стека потока в байтах / потоку по умолчанию выделяется 1 Mb стека
	// lpStartAddress - thread / адрес функции  / указываем название функции
	// lpParameter - sentence / адрес параметра / 
	// dwCreationFlags - 0 / флаги создания потока / если указываем ноль, то поток создаётся сразу
	// lpThreadId - &IDThread / идентификатор потока / переменная в которую windows помещает идентификатор потока

	if (hThread == NULL)
		return GetLastError();

	for (i = 0; i < j; i++)
		if (sentence[i] == 'a')
			k++;
	cout << "Number fo symbols 'a' in the string = " << k << endl;

	// ждем окончания разбора на лексемы
	WaitForSingleObject(hThread, INFINITE);

	// закрываем дескриптор потока thread
	CloseHandle(hThread);

	return 0;
}
