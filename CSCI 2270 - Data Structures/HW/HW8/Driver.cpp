#include "PriorityQueue.hpp"
#include <iostream>
#include <fstream>
// you may include more libraries as needed

using namespace std;


void menu()
{
  cout << "============Main Menu============" << endl;
  cout << "1. Get group information from file" << endl;
  cout << "2. Add a group to Priority Queue" << endl;
  cout << "3. Show next group in the queue" << endl;
  cout << "4. Serve Next group" << endl;
  cout << "5. Serve Entire Queue" << endl;
  cout << "6. Quit" << endl;
}

int main(int argc, char *argv[])
{
	PriorityQueue myQueue(stoi(argv[1]));
  string line;
	string choice;
	string fileName;

  string tempGroupName;
  int tempGroupSize;
  int tempCookingTime;

	while (choice != "6")
	{
		menu();
		getline(cin, choice);
		switch (stoi(choice))
		{
			case 1:
			{
        if (myQueue.isFull() == true)
        {
          cout << "Heap full, cannot enqueue" << endl;
          break;
        }

				cout << "Enter filename:" << endl;
        getline (cin, fileName);

        ifstream inFile;
        inFile.open(fileName);

        if (inFile.is_open())
        {
          while (inFile.peek() != EOF)
          {
            getline(inFile, line, ' ');
            tempGroupName = line;

            getline(inFile, line, ' ');
            tempGroupSize = stoi(line);

            getline(inFile, line, '\n');
            tempCookingTime = stoi(line);

            myQueue.enqueue(tempGroupName, tempGroupSize, tempCookingTime);

            if (myQueue.isFull() == true)
            {
              cout << "Heap full, cannot enqueue" << endl;
              break;
            }
          }
        }


				break;
			}
			case 2:
			{
        if (myQueue.isFull() == true)
        {
          cout << "Heap full, cannot enqueue" << endl;
          break;
        }

				cout << "Enter Group Name: " << endl;
        getline(cin, line);
        tempGroupName = line;

        cout << "Enter Group Size: " << endl;
        getline(cin, line);
        tempGroupSize = stoi(line);

        cout << "Enter Estimated Cooking Time: " << endl;
        getline(cin, line);
        tempCookingTime = stoi(line);

        myQueue.enqueue(tempGroupName, tempGroupSize, tempCookingTime);

				break;
			}
			case 3:
			{
        if (myQueue.isEmpty() == true)
        {
          cout << "Heap empty, nothing to peek" << endl;
          break;
        }

        cout << "Group Name: " << myQueue.peek().groupName << endl;
        cout << "Group Size: " << myQueue.peek().groupSize << endl;
        cout << "Group Time: " << myQueue.peek().cookingTime << endl;

        break;
			}
      case 4:
			{
        if (myQueue.isEmpty() == true)
        {
          cout << "Heap empty, cannot dequeue" << endl;
          break;
        }

        int totalCookTime = 0;
        totalCookTime += myQueue.peek().cookingTime;

        cout << "Group Name: " << myQueue.peek().groupName << " - Total Cook Time for the Group: " << totalCookTime << endl;

        myQueue.dequeue();
        break;
			}
      case 5:
			{
        int totalCookTime = 0;
        if (myQueue.isEmpty() == true)
        {
          cout << "Heap empty, cannot dequeue" << endl;
          break;
        }

        while (myQueue.isEmpty() == false)
        {
          totalCookTime += myQueue.peek().cookingTime;
          cout << "Group Name: " << myQueue.peek().groupName << " - Total Cook Time for the Group: " << totalCookTime << endl;
          myQueue.dequeue();
        }
        break;
			}
      case 6:
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
