#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct User
{
  string username;
  float gpa;
  int age;
};

void addUser(User users[], string _username, float _gpa, int _age, int length)
{
  if (length == 0)
  {
    users[0].username = _username;
    users[0].gpa = _gpa;
    users[0].age = _age;
  }
  else
  {
    for (int j = 1; j < length + 1; j++)
    {
      if (users[j].username == "")
      {
        users[j].username = _username;
        users[j].gpa = _gpa;
        users[j].age = _age;
        break;
      }
    }
  }
}

void printList(const User users[], int length)
{
  for (int k = 0; k < length; k++)
  {
    cout << users[k].username << " [" << users[k].gpa << "] age: " << users[k].age << endl;
  }
}

int main (int argc, char *argv[])
{
  int maxArray = 100;
  int numEntries = 0;
  User users[maxArray];
  string line;
  string tempName;
  float tempGpa;
  int tempAge;
  //float minGpa = argv[1];

  ifstream inFile;
  inFile.open(argv[1]);

  if (inFile.is_open())
  {
    while (inFile.peek() != EOF)
    {
      getline(inFile, line, ',');
      tempName = line;

      getline(inFile, line, ',');
      tempGpa = stof(line);

      getline(inFile, line, '\n');
      tempAge = stoi(line);

      addUser(users, tempName, tempGpa, tempAge, numEntries);
      numEntries++;

    }
  }
  printList(users, numEntries);

  ofstream outFile(argv[2]);
  for (int l = 0; l < numEntries; l++)
  {
    if (users[l].gpa >= stof(argv[3]))
    {
      outFile << users[l].username;
      outFile << "," << users[l].gpa;
      outFile << ",";
      outFile << users[l].age << endl;
    }

  }
}
