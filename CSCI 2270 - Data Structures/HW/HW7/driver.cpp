#include "HashTable.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
// you may include more libraries as needed

using namespace std;

/* load stopwords into the stopwords hash table */
int main(int argc, char *argv[])
{
  if (argc != 5)
  {
    cout << "not enough arguments" << endl;
    return 0;
  }

  HashTable *stopTable = new HashTable(STOPWORD_TABLE_SIZE);

  getStopWords(argv[3], *stopTable);

  HashTable uniqueTable(stoi(argv[4]));

  string line;

  ifstream inFile;
  inFile.open(argv[2]);

  if (inFile.is_open())
  {
    while (inFile >> line)
    {
      if (!uniqueTable.isInTable(line) && !isStopWord(line, *stopTable))
      {
        uniqueTable.addWord(line);
      }
      else if (uniqueTable.isInTable(line) && !isStopWord(line, *stopTable))
      {
        uniqueTable.incrementCount(line);
      }
    }
  }
  else
  {
    cout << "file not opened" << endl;
  }

  uniqueTable.printTopN(stoi(argv[1]));

  cout << "#" << endl << "Number of collisions: " << uniqueTable.getNumCollisions() << endl;
  cout << "#" << endl << "Unique non-stop words: " << uniqueTable.getNumItems() << endl;
  cout << "#" << endl << "Total non-stop words: " << uniqueTable.getTotalNumWords() << endl;

  return 0;
}
