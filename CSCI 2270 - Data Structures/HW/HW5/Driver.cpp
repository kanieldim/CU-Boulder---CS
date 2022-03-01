#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
// you may include more libraries as needed

using namespace std;


void menu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
  cout << "2. Query movies" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Average Rating of movies" << endl;
  cout << "5. Quit" << endl;
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

      MT.addMovieNode(tempRanking, tempName, tempYear, tempRating);
    }
  }


	while (choice != "5")
	{
		menu();
		getline(cin, choice);
		switch (stoi(choice))
		{
			case 1:
			{
				cout << "Enter title:" << endl;
				getline (cin, choice1);
				MT.findMovie(choice1);
				break;
			}
			case 2:
			{
				cout << "Enter minimum rating:" << endl;
        getline (cin, choice2);
        cout << "Enter minimum year:" << endl;
        getline (cin, choice3);

        MT.queryMovies(stof(choice2), stoi(choice3));
				break;
			}
			case 3:
			{
				MT.printMovieInventory();
				break;
			}
      case 4:
      {
        MT.averageRating();
        break;
      }
      case 5:
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
