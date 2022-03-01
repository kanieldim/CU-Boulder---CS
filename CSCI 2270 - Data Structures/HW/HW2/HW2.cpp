#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

struct wordItem
{
  string word;
  int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
  string line;
  int ID = 0;

  ifstream inFile;
  inFile.open(ignoreWordFileName);

  if(inFile.is_open())
  {
    while (getline(inFile,line))
    {
      ignoreWords[ID] = line;
      ID++;
    }
    inFile.close();
  }
  else
  {
    cout << "Failed to open " << ignoreWordFileName << endl;
  }
}

bool isStopWord(string word, string ignoreWords[])
{
  for (int i = 0; i < 50; i++)
  {
    if (word == ignoreWords[i])
    {
      return true;
    }
  }
  return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
  int totalCount = 0;

  for(int i = 0; i < length; i++)
  {
    totalCount += uniqueWords[i].count;
  }
  return totalCount;
}

void arraySort(wordItem uniqueWords[], int length)
{
  string sameWord;
  int frequentWords = 0;
  wordItem tempWords;

  for(int i = 0; i < length; i++)
  {
    for(int j = 0; j < length-1; j++)
    {
      if(uniqueWords[j].count < uniqueWords[j+1].count)
      {
        tempWords = uniqueWords[j];
        uniqueWords[j] = uniqueWords[j+1];
        uniqueWords[j+1] = tempWords;
      }
    }
  }
}

void printTopN(wordItem uniqueWords[], int topN, int totalNumWords)
{
  for (int i = 0; i < topN; i++)
  {
    cout << setprecision(4) << fixed << (float) uniqueWords[i].count / totalNumWords << " - " << uniqueWords[i].word << endl;
  }
}


int main(int argc, char *argv[])
{
  int maxID = 100;
  string word;
  int numArrDouble = 0;
  bool result;
  bool sameOrDifferent = false;
  int newMaxID;
  string ignoreWords[50];
  int nonStopWords = 0;
  int uniqueWordsCount = 0;
  int line = 0;

  wordItem *wordItemArr = new wordItem[maxID];

  if (argc != 4)
  {
    cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
    exit(0);
  }
  else
  {
    nonStopWords = getTotalNumberNonStopWords(wordItemArr, 100);

    getStopWords(argv[3], ignoreWords);

    ifstream readFile;
    readFile.open(argv[2]);

    if (readFile.is_open())
    {
      while(readFile.peek() != EOF)
      {
        getline(readFile, word, ' ');
        result = isStopWord(word, ignoreWords);
        if (result == true)
        {
          continue;
        }
        else
        {
          uniqueWordsCount++;
          for (int i = 0; i < maxID; i++)
          {
            if (word == wordItemArr[i].word)
            {
              wordItemArr[i].count++;
              sameOrDifferent = true;
            }
          }
          if (sameOrDifferent == false)
          {
            nonStopWords++;
            wordItemArr[nonStopWords].word = word;
            wordItemArr[nonStopWords].count++;

            if ((maxID - 1) == nonStopWords)
            {
              numArrDouble += 1;
              newMaxID = 2 * maxID;
              wordItem *newArray = new wordItem[newMaxID];

              for (int j = 0; j < maxID; j++)
              {
                newArray[j].word = wordItemArr[j].word;
                newArray[j].count = wordItemArr[j].count;
              }
              maxID = newMaxID;
              delete[] wordItemArr;
              wordItemArr = newArray;
            }
          }
          line++;
          sameOrDifferent = false;
        }
      }
    }

  cout << "Array doubled: " << numArrDouble << endl;
  cout << "#" << endl;
  cout << "Unique non-common words: " << nonStopWords << endl;
  cout << "#" << endl;
  cout << "Total non-common words: " << uniqueWordsCount << endl;
  cout << "#" << endl;
  cout << "Probabilities of top " << argv[1] << " most frequent words" << endl;
  cout << "---------------------------------------" << endl;

  int topN = stoi(argv[1]);
  arraySort(wordItemArr, nonStopWords);
  printTopN(wordItemArr, topN, line);

  }

}
