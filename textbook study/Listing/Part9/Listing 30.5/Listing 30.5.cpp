#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	char file_name[] = "D:\\Demo.bin";
	int a[10];

	ifstream in(file_name, ios::in | ios::binary);

	if (!in)
	{
		cerr << "File constructor failed." << endl;
		return 0;
	}
	
	cout << "Final array: ";
	
	for (int i = 0; i < 10; ++i)
	{
		in.read((char*)&a[i], sizeof(int));
		cout << a[i] << ' ';
	}
	cout << endl;
	
	in.close();
	
	system("pause");

	return 0;
}