/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
  string choice;
  CountryNetwork country;
  string nameCountry;
  string messageNote;
  string countryReceiving;
  string newCountry;
  bool result;

  while (choice != "8")
  {
    displayMenu();
    getline(cin, choice);
    switch (stoi(choice))
    {
      case 1:
        country.loadDefaultSetup();
        country.printPath();
        cout << endl;
        break;
      case 2:
        country.printPath();
        break;
      case 3:
        cout << "Enter name of the country to receive the message: ";
        getline (cin, countryReceiving);
        cout << endl;
        cout << "Enter the message to send: ";
        getline (cin, messageNote);
        cout << endl;
        cout << endl;
        country.transmitMsg(countryReceiving, messageNote);
        break;
      case 4:
        Country *prev;
        cout << "Enter a new country name:" << endl;
        getline (cin, newCountry);
        cout << "Enter the previous country name (or First):" << endl;
        getline (cin, nameCountry);
        prev = country.searchNetwork(nameCountry);
        while (prev == nullptr)
        {
          if(nameCountry == "First")
          {
            country.insertCountry(prev, newCountry);
            country.printPath();
            break;
          }
          else
          {
            cout << "INVALID country...Please enter a VALID previous country name:" << endl;
            cout << endl;
            getline(cin, nameCountry);
            prev = country.searchNetwork(nameCountry);
          }
        }
        if (prev != nullptr)
        {
          country.insertCountry(prev, newCountry);
          country.printPath();
        }
        break;
      case 5:
        cout << "Enter a country name: " << endl;
        getline(cin, nameCountry);
        country.deleteCountry(nameCountry);
        country.printPath();
        break;
      case 6:
        country.reverseEntireNetwork();
        country.printPath();
        cout << endl;
        break;
      case 7:
        country.deleteEntireNetwork();
        cout << "Deleted network" << endl;
        break;
      case 8:
        cout << "Quitting... cleaning up path: " << endl;
        country.printPath();
        if (country.isEmpty() == true)
        {
            cout << "Path cleaned" << endl;
            cout << "Goodbye!" << endl;
            break;
        }
        else
        {
          country.deleteEntireNetwork();
          cout << "Deleted network" << endl;
          result = country.isEmpty();
          if (result == false)
          {
            cout << "Error: Path NOT cleaned" << endl;
          }
          else
          {
            cout << "Path cleaned" << endl;
          }
            cout << "Goodbye!" << endl;
        }
        break;
      default:
        cout << "invalid input" << endl << endl;
    }
  }
}

/*
 * Purpose: displays a menu with options
 */
void displayMenu()
{
    //cout << endl;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Delete Country " << endl;
    cout << " 6. Reverse Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
