#pragma once

template<class T> class Vector2Template // TΝ^ͺΔ’ι
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x;
	T y;

	// γόZq
	Vector2Template& operator = (const Vector2Template& vec);

	//Y¦Zq
	int& operator[](T i);

	// δrZq
	bool operator == (const Vector2Template& vec) const;

	bool operator != (const Vector2Template& vec) const;

	bool operator > (const Vector2Template& vec) const;

	bool operator >= (const Vector2Template& vec) const;

	bool operator < (const Vector2Template& vec) const;

	bool operator <= (const Vector2Template& vec) const;


	// PZq
	Vector2Template& operator += (const Vector2Template& vec);

	Vector2Template& operator -= (const Vector2Template& vec);

	Vector2Template& operator *= (T k);

	Vector2Template& operator /= (T k);

	Vector2Template operator +()const;

	Vector2Template operator -()const;

};
	// ΝήΈΔΩΜZ

	// Vector2 + int
    template<class T>
	Vector2Template<T> operator+(const Vector2Template<T>& u, T v);

	// Vector2 - int
	template<class T>
	Vector2Template<T> operator-(const Vector2Template<T>& u, T v);

	// Vector2 + Vector2
	template<class T>
	Vector2Template<T> operator+(const Vector2Template<T>& u, const Vector2Template<T>& v);

	// Vector2 - Vector2
	template<class T>
	Vector2Template<T> operator-(const Vector2Template<T>& u, const Vector2Template<T>& v);

	// Vector2 * Vector2
	template<class T>
	Vector2Template<T> operator*(const Vector2Template<T>& u, const Vector2Template<T>& v);

	// Vector2 / Vector2
	template<class T>
	Vector2Template<T> operator/(const Vector2Template<T>& u, const Vector2Template<T>& v);

	// Vector2 % Vector2
	template<class T>
	Vector2Template<T> operator%(const Vector2Template<T>& u, const Vector2Template<T>& v);

	// Vector2 % int
	template<class T>
	Vector2Template<T> operator%(const Vector2Template<T>& u, T v);

	// Vector2 * int
	template<class T>
	Vector2Template<T> operator*(const Vector2Template<T>& u, T v);

	// int * Vector2
	template<class T>
	Vector2Template<T> operator*(T u, Vector2Template<T>& v);

	// Vector2 / int
	template<class T>
	Vector2Template<T> operator/(const Vector2Template<T>& u, T v);

	// βΞl
	template<class T>
	Vector2Template<T> abs(const Vector2Template<T>& u);

	using Vector2 = Vector2Template<int>;
	using Vector2Dbl = Vector2Template<double>;
	using Vector2Flt = Vector2Template<float>;

#include <common/detauls/Vector2.h>