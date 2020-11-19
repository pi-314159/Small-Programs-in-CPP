#include <iostream>
#include <limits>
#include <cstring>

using namespace std;

template <class T, class U>
class palindrome
{
    T inputString = (char*)malloc(1000000), finalStr = (char*)malloc(1000000);
    U strLen, i, I;

    public:
        palindrome(T input_buff1, U input_buff2)
        {
            inputString = input_buff1;
            strLen = input_buff2;
        }

        T cleanText() // This will also convert text to lowercase.
        {
            I = 0;
            for (i = 0; i < strLen; i++)
			{
			    if ((int(inputString[i]) > 96 && int(inputString[i]) < 123) || (int(inputString[i]) > 47 && int(inputString[i]) < 58))
				{
					inputString[I] = inputString[i];
					++I;
				}
				else if (int(inputString[i]) > 64 && int(inputString[i]) < 91)
				{
				    inputString[I] = char(int(inputString[i]) + 32);
					++I;
				}
			}
			inputString[I] = '\0';
			strLen = strlen(inputString);
			return inputString;
        }

        T reverseText();

        bool isPalindrome()
        {
            I = 1;
            for (i = 0; i < strLen; i++)
			{
			    I = (finalStr[i] == inputString[i] ? 0 : 1);
			}
			clean_free();
			switch (I)
			{
                case 1:
                    return false;
                case 0:
                    return true;
			}
        }

        void clean_free()
        {
            free(inputString);
            free(finalStr);
            return;
        }
};

template <class T, class U>
T palindrome<T, U>::reverseText()
{
    for (int i = 0, I = strLen - 1; i < strLen; i++, I--) {
        finalStr[I] = inputString[i];
    }
    finalStr[strLen] = '\0';
    return finalStr;
}

int main()
{
    char * input  = (char*)malloc(1000000);

    cout << "Please enter a sentence: \n";
    cin.getline(input, 1000000);

    palindrome <char*, int> pal(input, strlen(input));
    pal.cleanText();
    pal.reverseText();
    if (pal.isPalindrome() == true)
    {
        cout << "It is a palindrome. \n";
    } else
    {
        cout << "It is NOT a palindrome. \n";
    }
    return 0;
}
