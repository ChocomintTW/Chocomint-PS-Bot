#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <windows.h>
#include <algorithm>
#include <complex>
#include "header-src/stringEX.h"
using namespace std;

#define ifyouusethisyourprogramwillbefasterthanbefore ios::sync_with_stdio(false), cin.tie(nullptr);

complex<double> stoc(string &str)
{
	complex<double> result;
	stringEX tmp = str;
	tmp.replaceAll(" ", "\0");
	auto complex_vec = tmp.split("+");
	if (complex_vec.size() == 1)
		auto complex_vec = tmp.split("-");

	if (complex_vec.size() == 2)
	{
		try
		{
			result.real(stod(complex_vec[0]));
			auto im = complex_vec[1];
			if (*(im.end() - 1) == 'i')
				result.imag(stod(im.substr(0, im.size() - 1)));
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return result;
}

int main()
{
	string s = "132.4-3212.1i";
	cout << stoc(s) << "\n";
	return 0;
}
