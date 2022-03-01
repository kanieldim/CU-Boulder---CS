#include <iostream>
#include "HashTable.hpp"

using namespace std;

HashTable :: HashTable(int hashTableSize)
{
  this -> hashTableSize = hashTableSize;
  hashTable = new wordItem*[hashTableSize];
  for (int i = 0; i < hashTableSize; i++)
  {
    hashTable[i] = nullptr;
  }
  numCollisions = 0;
  numItems = 0;
}

HashTable :: ~HashTable()
{
  delete hashTable;
}

void HashTable :: addWord(string word)
{
  if (!searchTable(word))
  {

    int index = getHash(word);
    wordItem *temp = hashTable[index];
    wordItem *temp2 = new wordItem;
    temp2 -> word = word;
    temp2 -> count = 1;
    temp2 -> next = nullptr;
    if (hashTable[index] == nullptr)
    {
        hashTable[index] = temp2;
        numItems++;
    }
    else
    {
        while (temp -> next != nullptr)
        {
            temp = temp -> next;
        }
        temp -> next = temp2;
        numItems++;
        numCollisions++;
    }

    return;
  }
  else
  {
    cout << "duplicate entry: " << word << endl;
    return;
  }

}

bool HashTable :: isInTable(string word)
{
  wordItem *found = searchTable(word);
  if (found == nullptr)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void HashTable :: incrementCount(string word)
{

  int add;
  //cout << "here1" << endl;
  wordItem *temp = searchTable(word);
  //cout << "here2" << endl;
  add = temp -> count;
  //cout << "here3" << endl;
  temp -> count = add + 1;
  //cout << "here4" << endl;
}

void HashTable :: printTopN(int n)
{
  int totalNumber = getTotalNumWords();
  int vectorSize = 0;
  bool switched = false;
  wordItem *temp = new wordItem;
  vector <wordItem *> arraySort;

  for (int i = 0; i < hashTableSize; i++)
  {
    temp = hashTable[i];
    while (temp != nullptr)
    {
      arraySort.push_back(temp);
      temp = temp -> next;
    }
  }
  vectorSize = arraySort.size();
  for (int j = 0; j < (vectorSize - 1); j++)
  {
    for (int k = 0; k < (vectorSize - j - 1); k++)
    {
      if (arraySort[k + 1] -> count > arraySort[k] -> count)
      {
        swap(arraySort[k], arraySort[k+1]);
        switched = true;
      }
    }
  }
  if (switched == false)
  {
    return;
  }
  for (int i = 0; i < n; i++)
  {
    cout << fixed << setprecision(4) << (float) arraySort[i] -> count / totalNumber << " - " << arraySort[i] -> word << endl;
  }
}

int HashTable :: getNumCollisions()
{
  return numCollisions;
}

int HashTable :: getNumItems()
{
  return numItems;
}
int HashTable::getTotalNumWords()
{
    int totalWords = 0;
    for (int i = 0; i < hashTableSize; i++)
    {
        wordItem *temp = hashTable[i];
        while (temp != nullptr)
        {
            totalWords += temp -> count;
            temp = temp -> next;
        }
    }
    return totalWords;
}

unsigned int HashTable :: getHash(string word)
{
  unsigned int hashValue = 5381;
  int length = word.length();
  for (int i=0;i<length;i++)
  {
    hashValue=((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}

wordItem* HashTable :: searchTable(string word)
{
  int index = getHash(word);
  wordItem *temp = hashTable[index];
  while (temp != nullptr)
  {
    if (temp -> word == word)
    {
      return temp;
    }
    else
    {
      temp = temp -> next;
    }
  }

  return nullptr;
}

void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable)
{
    string line;


    ifstream inFile;
    inFile.open(ignoreWordFileName);

    if (inFile.is_open())

    {
        while (inFile >> line)
        {
            stopWordsTable.addWord(line);
        }
    }
}
/* check table to see if a word is a stopword or not */
bool isStopWord(string word, HashTable &stopWordsTable)
{

  bool result = stopWordsTable.isInTable(word);
  return result;
}
