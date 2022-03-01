#include <iostream>
#include <fstream>

using namespace std;

int insertIntoSortedArray ( int myArray[], int numEntries, int newValue)
{
  if (numEntries == 0)
  {
    myArray[0] = newValue;
    numEntries++;
  }
  else
  {
    int arrayID = -1;
    for (int j = 0; j < numEntries; j++)
    {
      if (newValue < myArray[j])
      {
        arrayID = j;
        break;
      }
    }
    if (arrayID == -1)
    {
      myArray[numEntries] = newValue;
    }
    else
    {
      for (int k = numEntries - 1; k >= arrayID; k--)
      {
        myArray[k + 1] = myArray[k];
      }
      myArray[arrayID] = newValue;
    }
    numEntries++;
  }

  return numEntries;
}

int main (int argc, char *argv[])
{
  int numEntries1 = 100;
  int array[numEntries1];
  string line = "";
  int size = 0;
  int value;
  int i = 0;
  int result = 0;

  ifstream inFile;
  inFile.open(argv[1]);

  if (inFile.is_open())
  {
    while (getline(inFile, line))
    {
      value = stoi(line);
      result = insertIntoSortedArray(array, result, value);

      for (int i = 0; i < result; i++)
      {
        if (i == (result - 1))
        {
          cout << array[i] << endl;
        }
        else if (i < result)
        {
          cout << array[i] << ",";
        }
      }
    }
  }
  else
  {
    cout << "Failed to open the file." << endl;
  }

}
