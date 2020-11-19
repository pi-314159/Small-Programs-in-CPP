#include <iostream>
#include <limits>
#include <climits>

#define ullint unsigned long long int
typedef unsigned long long int * ullintptr;

using namespace std;

template <class T>
class FibonacciSequence
{
    T retVal, reqItemLength;
    ullint first = 0, last = 1, temp, i;

    public:
        FibonacciSequence(T input_buff)
        {
            reqItemLength = input_buff;
        }

        T makeFibSeries()
        {
            retVal = new ullint[*reqItemLength];
            for (i = 0; i < *reqItemLength; i++)
            {
                retVal[i] = last;
                temp = first;
                first = last;
                last += temp;
            }
            return retVal;
        }
};

int main()
{
    ullint reqItems;

    cout << "How many numbers do you want? (The first 0 does not count) ";

    while ((!(cin >> reqItems)) || (reqItems > 93) || (reqItems < 1)) // Validate the input.
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Due to the IDE limitation, the number should be smaller than 2^64 and bigger than 0." << endl;
		cout << "How many numbers do you want? (The first 0 does not count) ";
	}

    FibonacciSequence <ullintptr> FS(&reqItems);

    ullintptr retVal = FS.makeFibSeries();

    cout << "The requested Fibonacci Sequence is: \n";
    for (int i = 0; i < reqItems; i++) cout << *(retVal + i) << " ";

    delete[] retVal;
    return 0;
}
