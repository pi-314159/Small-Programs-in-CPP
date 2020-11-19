template <class T>
Circle<T>::Circle(T R)
{
	r = R;
}
template <class T>
T Circle<T>::Area()
{
	return 3.14159265 * r * r;
}
template <class T>
T Circle<T>::C()
{
	return 3.14159265 * 2 * r;
}

Circle<int>::Circle(int R)
{
	r = R;
}
int Circle<int>::Area()
{
	return 3.14 * r * r;
}
Circle<int>::~Circle()
{
//	#include <iostream>
//	std::cout << "Memory freed.\n";
}
