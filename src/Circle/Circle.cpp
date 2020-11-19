#include <iostream>
#include <iomanip>
#include "Circle.h"

using namespace std;

int main()
{
	Circle <double> c1(5.6);
	cout << "The area of a circle (which radius is 5.6) is " << c1.Area() << ".\n";

	Circle <int> * c2 = new Circle <int> (5);
	cout << "The area of a circle (which radius is 5) is " << c2->Area() << ".\n";
	delete c2;

	Circle <double> c3(9.2);
	cout << "The circumference of a circle (which radius is 9.2) is " << c3.C() << ".\n";

	return 0;
}
