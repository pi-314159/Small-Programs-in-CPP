// You need a C++ compiler that supports C++11 or later versions of C++.
// This program is licensed under the MIT license.
// Author: PI.
// Date: April 2, 2018.

#include <iostream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <limits>

using namespace std;

int main()
{
	int ogNum, num, square;
	string firstDigit, lastDigit, firstPart, midPart, lastPart, midPartExceptLastDigit, lastPartFirstDigit;
	stringstream addZero_2, addZero_3;

	cout << "Please enter an integer between -100 and 100: ";

	while ((!(cin >> num)) || (num > 100) || (num < -100)) { // Validate the input.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please double-check your input number, it must be an INTEGER between -100 and +100!" << endl;
		cout << "Please input a new number here: ";
	}

	ogNum = num;
	num = abs(num);
	if (num < 10) {
		square = pow(num, 2); // Or it can be written as: sqaure = num * num.
	}
	else if (num == 100) {
		square = 10000;
	}
	else {
		firstDigit = to_string(num)[0];
		lastDigit = to_string(num)[1];

		lastPart = to_string(stoi(lastDigit) * stoi(lastDigit)); // Another way to write pow().
		addZero_2 << setfill('0') << setw(2) << lastPart; // Add zeros in front of the number and make it a two digit number.
		lastPart = addZero_2.str();
		lastPartFirstDigit = lastPart[0];
		lastPart = lastPart[1];

		midPart = to_string(stoi(firstDigit) * (stoi(lastDigit) + stoi(lastDigit)) + stoi(lastPartFirstDigit));
		addZero_3 << setfill('0') << setw(3) << midPart; // Add zeros in front of the number and make it a three digit number.
		midPart = addZero_3.str();
		midPartExceptLastDigit = midPart;
		midPartExceptLastDigit.pop_back();
		midPart = midPart.substr(midPart.length() - 1);

		firstPart = to_string(stoi(firstDigit) * stoi(firstDigit) + stoi(midPartExceptLastDigit));

		square = stoi(firstPart + midPart + lastPart);
	}

	cout << "\n" << ogNum << " to the power of TWO is: " << square << "." << endl;
	cout << "\n" << "Copyright 2018 PI. All rights reserved." << endl;

	system("pause");
	return 0;
}
