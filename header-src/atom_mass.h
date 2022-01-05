#ifndef _ATOM_MASS_H_
#define _ATOM_MASS_H_

#include <iostream>
#include <map>
#include "stringEX.h"

namespace std
{
	const string atom_name[93] = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Rh", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U"};
	const double atom_mass[93] = {1.008, 4.003, 6.941, 9.012, 10.811, 12.011, 14.007, 15.999, 18.998, 20.18, 22.99, 24.305, 26.982, 28.086, 30.974, 32.065, 35.453, 39.098, 39.948, 40.078, 44.956, 47.867, 50.942, 51.996, 54.938, 55.845, 58.693, 58.933, 63.546, 65.39, 69.723, 72.64, 74.922, 78.96, 79.904, 83.8, 85.468, 87.62, 88.906, 91.224, 92.906, 95.94, 98, 101.07, 102.906, 106.42, 107.868, 112.411, 114.818, 118.71, 121.76, 126.905, 127.6, 131.293, 132.906, 137.327, 138.906, 140.116, 140.908, 144.24, 145, 150.36, 151.964, 157.25, 158.925, 162.5, 164.93, 167.259, 168.934, 173.04, 174.967, 178.49, 180.948, 183.84, 186.207, 190.23, 192.217, 195.078, 196.967, 200.59, 204.383, 207.2, 208.98, 209, 210, 222, 223, 226, 227, 231.036, 232.038, 237};
	map<string, double> atoms;

	void AtomInit()
	{
		for (int i = 0; i < 93; i++)
			atoms[atom_name[i]] = atom_mass[i];
	}

	bool isBig(char c) { return (c >= 'A' && c <= 'Z'); }
	bool isNumber(char c) { return (c >= '0' && c <= '9'); }

	double mass(string &formula)
	{
		if (atoms.size() == 0)
			throw "You didn't initialize the system";

		stringEX f = formula;
		int size = f.size();
		for (int i = 0; i < size; i++)
		{
			if (i == size - 1)
				; // last
			else
			{
				auto single_ = f.substr(i, 1), double_ = f.substr(i, 2);
				double s = atoms[single_], d = atoms[double_];
				bool is_double = (d ? true : false);

				int cnt;
				for (int j = i + is_double + 1; isNumber(f[j]); j++, cnt++)
					;
				f.substr(i, cnt - 1);
			}
		}

		return 0.0;
	}
}

#endif // _ATOM_MASS_H_
