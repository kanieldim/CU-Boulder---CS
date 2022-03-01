#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include "Graph.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  Graph g;
  string cityNameArray[50];
  string line;
  string word;
  string city1;
  int i = 0;

  ifstream inFile;
  inFile.open(argv[1]);

  if (inFile.is_open())
  {
    getline(inFile, line);
    stringstream ss(line);

    getline(ss, word, ',');

    while(getline(ss, word, ','))
    {
        cityNameArray[i] = word;
        g.addVertex(cityNameArray[i]);
        i++;
    }

    while(getline(inFile, line))
    {
      i = 0;
      stringstream ss2(line);
      getline(ss2, word, ',');
      city1 = word;
      while(getline(ss2, word, ','))
      {
        if(word != "0" && word != "-1")
        {
            cout << " ... Reading in " << city1 << " -- " << cityNameArray[i] << " -- " << word << endl;
            g.addEdge(city1, cityNameArray[i], stoi(word));
        }
        i++;
      }
    }
  }

  cout << "------------------------------ " << endl
  << "Breadth First Traversal" << endl
  << "------------------------------" << endl;
  g.printBFT();
  cout << "------------------------------ " << endl
  << "Depth First Traversal" << endl
  << "------------------------------"<< endl;
  g.printDFT();
  cout << "------------------------------ " << endl
  << "Display Edges" << endl
  << "------------------------------"<< endl;
  g.displayEdges();


  return 0;
}
