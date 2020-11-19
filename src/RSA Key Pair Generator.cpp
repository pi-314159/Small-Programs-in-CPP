////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      This file has compiled in Microsoft Visual Studio Community 2017 (version: 15.6.4) successfully.      //
//                             This program is licensed under the MIT license.                                //
//                                               Author: PI.                                                  //
//                                           Date: May 14, 2018.                                              //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <random>
#include <math.h>
#include <tuple>
#include <limits>
#include <string>

using namespace std;

long long int getRandomNumber(unsigned long int rMin, unsigned long int rMax) // Generate a number.
{
	mt19937 randNumGen; // Based on Mersenne Twister.
	randNumGen.seed(random_device()());
	uniform_int_distribution<unsigned long int> numRange(rMin, rMax);

	return numRange(randNumGen);
}

long long int powerMod(long long int base, long long int exp, long long int modulus) // PowerMod Calculator.
{
	long long int mod = 1;
	base = base % modulus;

	while (exp > 0)
	{
		if (exp & 1)
		{
			mod = (mod * base) % modulus;
		}
		exp = exp >> 1;
		base = (base * base) % modulus;
	}
	return mod;
}

bool primeTest1(long long int testNum) // Prime Number Test 1: Fermat Primality Test.
{
	if (testNum % 3 == 0 || testNum % 5 == 0 || testNum % 7 == 0)
	{
		return false;
	}
	else
	{
		if (powerMod(3, testNum - 1, testNum) == 1 && powerMod(5, testNum - 1, testNum) == 1 && powerMod(7, testNum - 1, testNum) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool primeTest2(long long int testNum, long long int base) // Prime Number Test 2: Miller-Rabin Test.
{
	long long int k;
	long long int m, testNumA, b;
	k = 0;
	testNumA = testNum - 1;

	if (testNum % base == 0)
	{
		return false;
	}
	else
	{
		while (testNumA % 2 == 0)
		{
			k++;
			testNumA = testNumA / 2;
		}
		m = (testNum - 1) / pow(2, k);

		if (powerMod(base, m, testNum) == 1 || powerMod(base, m, testNum) == testNum - 1)
		{
			return true;
		}
		else
		{
			b = powerMod(base, m, testNum);

			while (b != 1 && b != testNum - 1)
			{
				b = powerMod(b, 2, testNum);
			}

			if (b == 1)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

tuple<long long int, long long int, long long int, long long int, long long int> extEuclideanAlgorithm(long long int p, long long int q) // Euclidean Algorithm & Extended Euclidean Algorithm Calculator
{
	long long int a1, a2, f1, f2, r1, r2, s1, s2, t1, t2;
	a1 = max(p, q);
	a2 = min(p, q);
	f1 = a1;
	f2 = a2;
	r1 = s2 = 1;
	r2 = s1 = 0;
	while (a2 > 0)
	{
		t1 = floor(a1 / a2);

		t2 = a2;
		a2 = a1 % a2;
		a1 = t2;

		t2 = r2;
		r2 = r1 - t1 * r2;
		r1 = t2;

		t2 = s2;
		s2 = s1 - t1 * s2;
		s1 = t2;
	}
	return make_tuple(a1, abs(r1), f1, abs(s1), f2);
}

long long int Euler_Totient(long long int n)
{
	long long int result = n;

	for (long long int p = 2; p * p <= n; ++p) {
		if (n % p == 0) {
			while (n % p == 0)
			{
				n /= p;
			}
			result -= result / p;
		}
	}

	if (n > 1)
	{
		result -= result / n;
	}
	return result;
}

int main()
{
	int keyDigit;
	unsigned long int pqMin, pqMax;
	long long int p, q, pMinus1, qMinus1, N, lcm, multCarmichael, key1, probKey;

	cout << "Please enter the length of the key (in digits): ";

	while ((!(cin >> keyDigit)) || (keyDigit > 9) || (keyDigit < 3)) // Validate the input.
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // GCC or Boost: Multiprecision supports 128-bit and bigger size of variables.
		cout << "Please double-check the length, it must be an INTEGER between 3 and 9!" << endl;
		cout << "Please enter the new length of the key here: ";
	}

	cout << "\n" << "The length of the key is: " << keyDigit << "." << endl;
	cout << "GENERATING THE KEY PAIR…" << "\n" << endl;

	pqMin = pow(10, keyDigit - 1);
	pqMax = pow(10, keyDigit) - 1;
	p = getRandomNumber(pqMin, pqMax);
	while (!primeTest1(p) || !primeTest2(p, 2) || !primeTest2(p, 37))
	{
		p = getRandomNumber(pqMin, pqMax);
	}
	q = getRandomNumber(pqMin, pqMax);
	while (p == q || !primeTest1(q) || !primeTest2(q, 2) || !primeTest2(q, 31))
	{
		q = getRandomNumber(pqMin, pqMax);
	}

	N = p * q;
	pMinus1 = p - 1;
	qMinus1 = q - 1;
	multCarmichael = qMinus1 * pMinus1;
	auto gcd = extEuclideanAlgorithm(pMinus1, qMinus1);
	lcm = multCarmichael / get<0>(gcd);

	key1 = getRandomNumber(pqMin, pqMax);
	while (key1 == q || key1 == p || !primeTest1(key1) || !primeTest2(key1, 2) || !primeTest2(key1, 83))
	{
		key1 = getRandomNumber(pqMin, pqMax);
	}

	auto genKey2 = extEuclideanAlgorithm(key1, lcm);
	if (get<2>(genKey2) == lcm)
	{
		probKey = get<3>(genKey2);
	}
	else
	{
		probKey = get<1>(genKey2);
	}

	if (probKey != key1 && probKey != 1)
	{
		long long int key2 = probKey;
		cout << "Your key is: " << endl;
		cout << "(" << key1 << ", " << key2 << ", " << N << ")" << endl;
	}
	else
	{
		long long int key2Exp = Euler_Totient(lcm) - 1;
		string key2 = to_string(key1) + "^" + to_string(key2Exp);
		cout << "Your key is: " << endl;
		cout << "(" << key1 << ", " << key2 << ", " << N << ")" << endl;
	}

	cout << "\n" << "Finished!" << endl;

	cout << "\n" << "Copyright 2018 PI. All rights reserved." << endl;

	system("pause");
	return 0;
}
