#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
// you may include more libraries as needed

using namespace std;


void menu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Print the inventory" << endl;
  cout << "2. Delete a movie" << endl;
  cout << "3. Quit" << endl;

}

int main(int argc, char *argv[])
{
	MovieTree MT;
  string line;
	string choice;
	string choice1;
	string choice2;
  string choice3;

  int tempRanking;
  string tempName;
  int tempYear;
  float tempRating;

  ifstream inFile;
  inFile.open(argv[1]);

  if (inFile.is_open())
  {
    while (inFile.peek() != EOF)
    {
      getline(inFile, line, ',');
      tempRanking = stoi(line);

      getline(inFile, line, ',');
      tempName = line;

      getline(inFile, line, ',');
      tempYear = stoi(line);

      getline(inFile, line, '\n');
      tempRating = stof(line);

      MT.addMovie(tempRanking, tempName, tempYear, tempRating);
    }
  }

	while (choice != "3")
	{
		menu();
		getline(cin, choice);
		switch (stoi(choice))
		{
			case 1:
			{
				MT.printMovieInventory();
				break;
			}
			case 2:
			{
				cout << "Enter a movie title:" << endl;
        getline (cin, choice2);
        MT.deleteMovie(choice2);
				break;
			}
			case 3:
			{
        cout << "Goodbye!" << endl;
        break;
			}
			default:
			{
				cout << "invalid input" << endl;
			}
		}

	}
}
