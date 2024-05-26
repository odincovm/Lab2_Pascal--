#include <iostream>
#include <string>
#include "../Include/Compiler.h"
using namespace std;
int main()
{
	try {
		Compiler cmp("C:\\PROGRAMMING\\Lab2_Pascal--\\Program.txt");
		cmp.compile();
	}
	catch (const char* error_message){
		cout << error_message << endl;
	}
}

