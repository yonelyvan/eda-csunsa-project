#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main()
{
	fstream file("1000names.txt");
	for (int i = 0 ; i< 1000 ;i++)
	{
		file<< "1000img/img"+to_string(i)+".ppm"<<endl;
	}
	return 0;
}