#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	char big[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	char sml[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

	CharToOem(big, big);
	CharToOem(sml, sml);
	
	cout << big << endl;
	cout << sml << endl;
	
	system("pause");

	return 0;
}
