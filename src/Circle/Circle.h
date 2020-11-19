#ifndef CIRCLE_H
#define CIRCLE_H

template <class T>
class Circle
{
	T r;
	public:
		Circle(T R);
		T Area();
		T C();
};
template <>
class Circle <int>
{
	int r;
	public:
		Circle(int R);
		int Area();
		~Circle();
};

#endif

#include "Circle.tpp"
