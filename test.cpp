#include <iostream>
#include <map>
#include "header-src/atom_mass.h"
using namespace std;

int main()
{
	string f = "Be6H2";
	AtomInit();
	try
	{
		cout << mass(f);
	}
	catch (const exception &e)
	{
		cout << e.what() << '\n';
	}

	return 0;
}
