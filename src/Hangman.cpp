// This code has compiled in g++ [gcc version 6.3.0 20170516 (Debian 6.3.0-18+deb9u1)] successfully.
// This program is licensed under the MIT license.
// Author: PI.
// Date: July 11, 2019.

#include <iostream>
#include <cstring>
#include <random>
#include <cctype>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

uint randNum(uint Min, uint Max) // Generate a random number.
{
	mt19937 MT; // Mersenne Twister - Just for fun.
	MT.seed(random_device()());
	uniform_int_distribution<uint> numRange(Min, Max);

	return numRange(MT);
}

class Game
{
	int maxAttemps = 5, minAttempt = 0, attempt = 1;
	string inputs = "00", word;

	public:
		Game(string word_buff, int yn)
		{
			transform(word_buff.begin(), word_buff.end(), word_buff.begin(), ::tolower);
			this->word = word_buff;
			cout << word << endl; // DEBUG ONLY!
			int initInputLen = word.length(), i;
			char * initInput  = (char*)malloc(initInputLen + 1);
			for (i = 0; i < initInputLen; i++)
			{
				initInput[i] = '*';
			}

			initInput[initInputLen] = '\0';

			cout << initInput << "\n";
			(yn == 1) ? this->whole() : this->partial(initInput, &initInputLen);
		}

		void whole()
		{
			while (minAttempt < maxAttemps)
			{
				cout << "Please enter the word: ";
				getline(cin, inputs);
				if (inputs == word)
				{
					cout << "CONGRATS! \nThe word is " << inputs << ".\nYou have used " << attempt << " guess";
					switch (attempt)
					{
						case 1 :
							cout << ".\n";
						default :
							cout << "es.\n";
					}
					return;
				} else
				{
					++minAttempt;
					++attempt;
					cout << "Please try again! \nThis is your " << minAttempt << " incorrect guess";
					if (minAttempt == 1)
					{
						cout << ".\n";
					} else
					{
						cout << "es.\n";
					}
				}
			}
			cout << "Sorry, you have failed five times! \nThe word is " << word << ".\n";
			return;
		}

		void partial(char * addr, int * initInputLen)
		{
			vector <char> unusedWord(word.begin(), word.end());
			int numLetters = 0;

			while (minAttempt < maxAttemps)
			{
				if (word == addr)
				{
					cout << "CONGRATS! \nThe word is " << word << ".\nYou have used " << attempt - 1 << " guess";
					switch (attempt - 1)
					{
						case 1 :
							cout << ".\n";
						default :
							cout << "es.\n";
					}
					return;
				}
				cout << "Please enter a lowercase letter: ";
				getline(cin, inputs);
				while (inputs.length() != 1 || int(inputs.at(0)) < 97 || int(inputs.at(0)) > 122)
				{
					cout << "You can only enter ONE LOWERCASE letter! \nPlease try again: ";
					getline(cin, inputs);
				}
				char replA[]  = "A";
				char preInputChar[1];
				preInputChar[0] = inputs[0];
				vector <char> inputChar = {*preInputChar};
				auto it = search(unusedWord.begin(), unusedWord.end(), inputChar.begin(), inputChar.end());
				int letterPos = it - unusedWord.begin();

				if (it != unusedWord.end())
				{
					++numLetters;
					++attempt;
					while (letterPos != *initInputLen)
					{
						unusedWord[letterPos] = *replA;
						addr[letterPos] = inputs[0];
						auto it = search(unusedWord.begin(), unusedWord.end(), inputChar.begin(), inputChar.end());
						letterPos = it - unusedWord.begin();
					}
					cout << "GREAT! You guessed one correct letter! \n" << addr << "\n";
				} else
				{
					++minAttempt;
					++attempt;
					cout << "Please try again! \nThis is your " << minAttempt << " incorrect guess";
					if (minAttempt == 1)
					{
						cout << ".\n";
					} else
					{
						cout << "es.\n";
					}
				}
			}
			cout << "Sorry, you have failed five times! \nThe word is " << word << ".\n";
			return;
		}
};

int main()
{
	char * y_or_n  = (char*)malloc(2);
	const char * YN = "YN";

	vector <string> DICT; // Compared with array, it is easier to get the number of elements.
	DICT.insert( DICT.end(), { "occupy", "valuable", "lopsided", "impeach", "brawny", "vivacious", "curtain",
	"comparison", "physical", "macabre", "quince" } );

	cout << "Welcome to the \"Hangman\" game! \nYou cannot carry out more than FIVE incorrect guesses! \n";
	cout << "Do you want to guess the whole word? [Y/n] ";
	while ((!(cin >> y_or_n)) || ((toupper(y_or_n[0]) != YN[0]) && (toupper(y_or_n[0]) != YN[1])))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Do you want to guess the whole word? [Y/n] ";
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	Game * Hangman = new Game(DICT[randNum(0, DICT.size() - 1)], (toupper(y_or_n[0]) == YN[0]) ? 1 : 2);
	DICT.clear();

	delete Hangman;
	return 0;
}
