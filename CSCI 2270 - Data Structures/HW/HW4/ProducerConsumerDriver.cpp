/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
  cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer PC;
	string choice;
	string choice1;
	string choice2;
	int frontIndex;
	int number;

	while (choice != "3")
	{
		menu();
		getline(cin, choice);
		switch (stoi(choice))
		{
			case 1:
			{
				cout << "Enter the number of items to be produced:" << endl;
				getline (cin, choice1);
				for (int i = 0; i < stoi(choice1); i++)
				{
					cout << "Item" << i+1 << ":" << endl;
					getline (cin, choice2);
					PC.enqueue(choice2);
				}
				break;
			}
			case 2:
			{
				string *array = PC.getQueue();
				cout << "Enter the number of items to be consumed:" << endl;
				getline (cin, choice1);
				number = stoi(choice1);
				while (number != 0)
				{
					if (PC.queueSize() != 0)
					{
						frontIndex = PC.getQueueFront();
						cout << "Consumed: " << array[frontIndex] << endl;
						PC.dequeue();
						number--;
					}
					else
					{
						cout << "No more items to consume from queue" << endl;
						break;
					}
				}
				break;
			}
			case 3:
			{
				cout << "Number of items in the queue:" << PC.queueSize();
				break;
			}
			default:
			{
				cout << "invalid input" << endl;
			}
		}

	}
}
