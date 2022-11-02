#include <conio.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int i;
	cout << "I am created." << endl;
	cout << "My name is: " << argv[0] << endl;

	for (i = 1; i < argc; ++i)
		cout << "My " << i << " parameter = " << argv[i] << endl; 
	
	system("pause");
	return 0;
}