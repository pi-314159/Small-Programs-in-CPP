#include <iostream>
#include <random>
#include <ctime>
#include <cstring>
#include <algorithm>

using namespace std;

enum suits
{
	club = 1,
	diamond,
	heart,
	spade
};

int randNum(int Min, int Max) // Generate a random number.
{
	mt19937 MT; // Mersenne Twister - Just for fun.
	MT.seed(random_device()());
	uniform_int_distribution<int> numRange(Min, Max);

	return numRange(MT);
}

int dealACard (suits & suit, string & card)
{
	vector <string> cardInit = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
	"Jack", "Queen", "King" };
	vector <int> cardVal = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
	auto it = find(cardInit.begin(), cardInit.end(), card);
	int cardInitPos = it - cardInit.begin();
	return cardVal[cardInitPos];
}

int main()
{
    int rand1, rand2;

	vector <string> Cards = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
	"Jack", "Queen", "King" };
	vector <string> allCard = { "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "110", "111", "112",
	"20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "210", "211", "212",
    "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "310", "311", "312",
	"40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "410", "411", "412" };
	vector <string> Suits = { "Club", "Diamond", "Heart", "Spade" };

	char * y_or_n  = (char*)malloc(2);
	const char * YN = "YN";

	cout << "Do you want to start now? [Y/n] ";
	while ((!(cin >> y_or_n)) || ((toupper(y_or_n[0]) != YN[0]) && (toupper(y_or_n[0]) != YN[1])))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Do you want to start now? [Y/n] ";
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (toupper(y_or_n[0]) == YN[0])
    {
        if (allCard.size() < 8)
        {
            cout << "Cards are shuffled!\n";
            allCard = vector <string> { "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "110", "111", "112",
            "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "210", "211", "212",
            "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "310", "311", "312",
            "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "410", "411", "412" };
        }

        rand1 = randNum(1, 4);
        rand2 = randNum(0, 12);

        while (find(allCard.begin(), allCard.end(), to_string(rand1) + to_string(rand2)) == allCard.end())
        {
            rand1 = randNum(1, 4);
            rand2 = randNum(0, 12);
        }

        allCard.erase(remove(allCard.begin(), allCard.end(), to_string(rand1) + to_string(rand2)), allCard.end());

        suits selectedSuit = static_cast<suits>(rand1);
        int cardVal = dealACard(selectedSuit, Cards[rand2]);
        cout << "The value of the card is " << cardVal << ".\n";
        cout << "This card is " << Suits[rand1 - 1] << " " << Cards[rand2] << ".\n";
        cout << "There are " << allCard.size() << " cards left.\n";

        cout << "Do you want to get another card? [Y/n] ";
	    while ((!(cin >> y_or_n)) || ((toupper(y_or_n[0]) != YN[0]) && (toupper(y_or_n[0]) != YN[1])))
	    {
		    cin.clear();
	    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    cout << "Do you want to get another card? [Y/n] ";
	    }
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

	return 0;
}
