#include <windows.h>
#include <iostream>

// there is already a function called count in the std namespace :(
// в пространстве имён std уже имеется функция с названием count
// 
// https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?redirectedfrom=MSDN&view=msvc-170
// https://learn.microsoft.com/ru-ru/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-170


/// <summary>
/// Начнём с того, что в самом названии бибилиотек dll есть слово dynamic
/// Статические библиотеки создаются немного не так, как динамические, и в ссылках выше я указал ссылку на
/// официальную документацию, где описан метод создания и добавления статической библиотеки, у которой
/// расширение .lib, но никак не .dll.
/// </summary>
/// 
/// Следовательно весь код дальше просто не работает, а если и работает, то я слишком тупой, чтобы
/// довести его до ума, чтобы добавить ранее созданную динамическую библиотеку как статическую
/// по описанию из учебника 2006 года.

extern "C" __declspec(dllimport) int count;
extern "C" __declspec(dllimport) int Add(int n);
extern "C" __declspec(dllimport) int Sub(int n);

int main()
{

	std::cout << "Initial count = " << count << std::endl;
	std::cout << "count = " << Add(20) << std::endl;
	std::cout << "count = " << Sub(15) << std::endl;

	system("pause");

	return 0;
}