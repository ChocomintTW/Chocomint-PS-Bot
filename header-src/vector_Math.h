#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_

#include <iostream>
#include <vector>
#include <cmath>
#include "stringEX.h"

#define here cout << "here\n";

namespace std
{
	template <typename _Ty>
	class Vector3D
	{
	private:
		_Ty _x, _y, _z;

	public:
		Vector3D() : _x(0), _y(0), _z(0) {}
		Vector3D(_Ty x, _Ty y, _Ty z) : _x(x), _y(y), _z(z) {}
		_Ty getX() const { return _x; }
		_Ty getY() const { return _y; }
		_Ty getZ() const { return _z; }
		vector<_Ty> getVector() const { return {_x, _y, _z}; }

		Vector3D operator+(const Vector3D &_ref);
		Vector3D operator-(const Vector3D &_ref);

		Vector3D &operator+=(const Vector3D &_ref);
		Vector3D &operator-=(const Vector3D &_ref);

		_Ty magnitude() const { return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2)); };
		friend _Ty angle(const Vector3D &_A, const Vector3D &_B) { return dot(_A, _B) / (_A.magnitude() * _B.magnitude()); }

		friend ostream &operator<<(ostream &_os, const Vector3D &_v)
		{
			_os << "[" << _v.getX() << ", " << _v.getY() << ", " << _v.getZ() << "]";
			return _os;
		}
	};

	template <typename _Ty>
	Vector3D<_Ty> Vector3D<_Ty>::operator+(const Vector3D<_Ty> &_ref)
	{
		int x0 = this->_x + _ref.getX();
		int y0 = this->_y + _ref.getY();
		int z0 = this->_z + _ref.getZ();
		return Vector3D(x0, y0, z0);
	}

	template <typename _Ty>
	Vector3D<_Ty> Vector3D<_Ty>::operator-(const Vector3D<_Ty> &_ref)
	{
		_Ty x0 = this->_x - _ref.getX();
		_Ty y0 = this->_y - _ref.getY();
		_Ty z0 = this->_z - _ref.getZ();
		return Vector3D(x0, y0, z0);
	}

	template <typename _Ty>
	_Ty dot(const Vector3D<_Ty> &_A, const Vector3D<_Ty> &_B) { return _A.getX() * _B.getX() + _A.getY() * _B.getY() + _A.getZ() * _B.getZ(); }

	template <typename _Ty>
	Vector3D<_Ty> cross(const Vector3D<_Ty> &_A, const Vector3D<_Ty> &_B)
	{
		_Ty x0 = _A.getY() * _B.getZ() - _B.getY() * _A.getZ();
		_Ty y0 = _B.getX() * _A.getZ() - _A.getX() * _B.getZ();
		_Ty z0 = _A.getX() * _B.getY() - _B.getX() * _A.getY();
		return Vector3D<_Ty>(x0, y0, z0);
	}

	template <typename _Ty>
	Vector3D<_Ty> &Vector3D<_Ty>::operator+=(const Vector3D<_Ty> &_ref)
	{
		*this = *this + _ref;
		return *this;
	}

	template <typename _Ty>
	Vector3D<_Ty> &Vector3D<_Ty>::operator-=(const Vector3D<_Ty> &_ref)
	{
		*this = *this - _ref;
		return *this;
	}

	Vector3D<double> transfer_toVector3D(const string &_s)
	{
		auto tmp = stringEX(_s);
		if (*tmp.begin() == '[' && *(tmp.end() - 1) == ']')
		{
			tmp.erase(tmp.begin());
			tmp.erase(tmp.end() - 1);
			auto list = tmp.split(",");
			if (list.size() == 3)
			{
				double *coordinate = new double[3];
				for (int i = 0; i < 3; i++)
				{
					coordinate[i] = stod(list[i]);
				}
				return Vector3D<double>(coordinate[0], coordinate[1], coordinate[2]);
				delete coordinate;
			}
			else
				throw "Not Vector3D";
		}
		else
			throw "Not Vector3D";
	}
}

#endif // _VECTOR_MATH_H_
