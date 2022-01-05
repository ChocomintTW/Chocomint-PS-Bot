#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "header-src/stringEX.h"
#include "header-src/calculator.h"
#include "header-src/vector_Math.h"
#define err setColor(color::red)
#define reset setColor()
#define many cout << err << "Too many parameters\n" \
				  << reset
#define incf cout << err << "Incorrect format\n" \
				  << reset
#define lack cout << err << "Lack parameters\n" \
				  << reset
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
enum color
{
	black = 0,
	dark_blue = 1,
	dark_green = 2,
	dark_aqua,
	dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5,
	dark_pink = 5,
	dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11,
	cyan = 11,
	red = 12,
	purple = 13,
	pink = 13,
	magenta = 13,
	yellow = 14,
	white = 15
};

class setColor
{
public:
	color _text, _background;
	setColor() : _text(color::white), _background(color::black) {}
	setColor(color text) : _text(text), _background(color::black) {}
	setColor(color text, color background) : _text(text), _background(background) {}
};

ostream &operator<<(ostream &_os, const setColor &_cp)
{
	// colorattribute = foreground + background * 16
	// to get red text on yellow use 4 + 14*16 = 228
	// light red on yellow would be 12 + 14*16 = 236
	SetConsoleTextAttribute(hConsole, _cp._text + _cp._background * 16);
	return _os;
}

char *base_transfer(const char *ref, int base1, int base2)
{
	char *c, *c2;
	itoa(strtol(ref, &c, base1), c2, base2);
	return c2;
}

inline bool isNumber(const string &str) { return str.find_first_not_of("0123456789") == string::npos; }

void welcome()
{
	// ifstream ifs;
	// ifs.open("/Chocomint.txt", ios::in);
	// string tmp;
	// while (getline(ifs, tmp))
	// 	cout << tmp << "\n";
	// ifs.close();
	cout << "\n"
		 << reset << "                               " << reset << "|" << setColor(color::green) << "   ____   _                                          _\n"
		 << setColor(color::aqua) << " Chocomint's PS Bot            " << reset << "|" << setColor(color::green) << "  / ___| | |                                        (_)            _\n"
		 << setColor(color::aqua) << " Version 1.2.2                 " << reset << "|" << setColor(color::green) << " | |     | |___   _____   ____   _____   _________   _   _____   _| |_\n"
		 << reset << "                               " << reset << "|" << setColor(color::green) << " | |     |  _  | |  _  | |  __| |  _  | |  _   _  | | | |  _  | |_   _|\n"
		 << setColor(color::yellow) << " Website: https://chocomint.cf " << reset << "|" << setColor(color::green) << " | |___  | | | | | |_| | | |__  | |_| | | | | | | | | | | | | |   | |\n"
		 << reset << "                               " << reset << "|" << setColor(color::green) << "  \\____| |_| |_| |_____| |____| |_____| |_| |_| |_| |_| |_| |_|   |_|\n"
		 << reset << "\n";
}

void help()
{
	cout << reset
		 << "base [b1] [b2] [value]      | Transfer value with b1 to b2   \n"
		 << "calc [formula]              | Calculate the formula          \n"
		 << "to-char [int]               | Transfer int to char with ASCII\n"
		 << "to-int [char]               | Transfer char to int with ASCII\n"
		 << "vec-R [vector3D]            | The length (magnitude) of a Vector3D\n"
		 << "dot [vector3D] [vector3D]   | Dot product of two Vector3D\n"
		 << "cross [vector3D] [vector3D] | Cross product of two Vector3D\n"
		 << "cls                         | Just like the origin command\n"
		 << "exit                        | Exit Chocomint's PS Bot\n";
}

int main()
{
	SetConsoleTextAttribute(hConsole, 15);
	welcome();
	while (true)
	{
		cout << "Bot > ";
		stringEX function, first;
		getline(cin, function);

		if (function == "exit")
			return -1;

		auto input = function.split(" ");

		first = input[0];
		if (first == "help")
			help();
		else if (first == "cls")
			system("cls");
		else if (first == "base")
		{
			if (input.size() < 4)
				lack;
			else
			{
				int base1 = stoi(input[1]);
				int base2 = stoi(input[2]);
				auto value = input[3].c_str();
				cout << base_transfer(value, base1, base2) << "\n";
			}
		}
		else if (first == "calc")
		{
			if (input.size() == 1)
				lack;
			else
			{
				input.erase(input.begin());
				stringEX tmp = Str_merge("", input);
				tmp.replaceAll(" ", "");
				cout << " = " << compute(infix_to_postfix(tmp)) << "\n";
			}
		}
		else if (first == "to-char")
		{
			if (input.size() == 2)
			{
				auto tmp = input[1];
				if (isNumber(tmp))
					cout << (char)stoi(tmp) << "\n";
				else
					cout << err << "Please input a \"number\"\n"
						 << reset;
			}
			else
				many;
		}
		else if (first == "to-int")
		{
			if (input.size() == 2)
			{
				if (input[1].size() == 1)
					cout << static_cast<int>(input[1][0]) << "\n";
				else
					cout << err << "Please input a \"char\"\n"
						 << reset;
			}
			else
				many;
		}
		else if (first == "vec-R")
		{
			input.erase(input.begin());
			stringEX tmp = Str_merge("", input);
			try
			{
				auto vec3d = transfer_toVector3D(tmp);
				cout << "R = " << vec3d.magnitude() << "\n";
			}
			catch (const char *e)
			{
				cout << err << e << reset << "\n";
			}
		}
		else if (first == "dot")
		{
			if (input.size() == 3)
			{
				Vector3D<double> vec1, vec2;
				try
				{
					vec1 = transfer_toVector3D(input[1]);
					vec2 = transfer_toVector3D(input[2]);
				}
				catch (const char *e)
				{
					cout << err << e << reset << "\n";
				}
				cout << dot(vec1, vec2) << "\n";
			}
			else
				incf;
		}
		else if (first == "cross")
		{
			if (input.size() == 3)
			{
				Vector3D<double> vec1, vec2;
				try
				{
					vec1 = transfer_toVector3D(input[1]);
					vec2 = transfer_toVector3D(input[2]);
				}
				catch (const char *e)
				{
					cout << err << e << reset << "\n";
				}
				cout << cross(vec1, vec2) << "\n";
			}
			else
				incf;
		}

		else
			cout << err << "No match command \"" << input[0] << "\"\n"
				 << reset;

		cout << ((first == "cls") ? "" : "\n"); // new line for command
	}

	return 0;
}
