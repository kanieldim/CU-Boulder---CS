#include <iostream>
#include "StackLL.hpp"

using namespace std;

#ifndef STACKLL_HPP
#define STACKLL_HPP

class StackLL
{
  private:
    //int *stackArray = new int[5];
    int stackHead;

  public:
    StackLL();
    ~StackLL();
    bool isEmpty();
    void push(int key);
    void pop();
    char peek();
};

#endif

// terminal debugger


StackLL::StackLL()
{
    //size = 5;
    stackHead = -1;
}

StackLL::~StackLL()
{
    while(!isEmpty())
        pop();
}

bool StackLL::isEmpty()
{
  if (stackHead == -1)
  {
    return true;
  }
  return false;
}

bool StackLL::isFull()
{
  if ((stackHead + 1) == size)
  {
    return true;
  }
  return false;
}

void StackLL::push(int key)
{
    if (isEmpty())
    {
      stackHead = 0;
      stackArray[stackHead] = key;
    }
    else if (isFull())
    {
      int newCapacity = (*size*2);
      int *newArray = new int[newCapacity];
      for (int i = 0; i < size; i++)
      {
        newArray[i] = (*stackArray)[i];
      }
      delete [] *stackArray;
      *stackArray = newArray;
      *size = newCapacity

      stackHead = stackHead + 1;
      stackArray[stackHead] = key;
    }
    else // if it is not empty nor full
    {
      stackHead = stackHead + 1;
      stackArray[stackHead] = key;
    }

}

void StackLL::pop()
{
  if (stackHead == 0)
  {
    stackHead = -1;
  }
  else if ((stackHead+1) <= size/2)
  {

  }
}

char StackLL::peek()
{
    if(!isEmpty())
        return stackHead->key;
    else{
        cout<<"empty stack. can not peek"<<endl;
        return -1;
    }
  //return 0;
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		return -1;
	}

	int size = 5;
	int *arrayPtr;

	// TODO Dynamically allocate space here for the array
	arrayPtr = new int[size];
	int numOfElement = 0;
	string temp;

	if(data.is_open())
	{
		while(getline(data, temp))
		{
			int toBeInsert = stoi(temp);
			if(numOfElement == capacity)
			{
				// Complete this function
				resize(&arrayPtr, &capacity);
			}
			arrayPtr[numOfElement] = toBeInsert;
			numOfElement++;
		}
		data.close();
	}

	for(int i = 0; i < numOfElement; i++)
	{
		cout << "Num: " << arrayPtr[i] << endl;
	}
	return 0;
}
