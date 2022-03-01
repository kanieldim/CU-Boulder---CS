/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
  head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
  if(head == nullptr)
  {
    return true;
  }
  return false;
}

/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
  if(previous == nullptr)
  {
    Country *temp = new Country;
    temp -> name = countryName;
    temp -> next = head;
    head = temp;
    temp = nullptr;
    cout << "adding: " << countryName << " (HEAD)" << endl;
  }
  else
  {
    Country *temp = new Country;
    temp -> name = countryName;
    temp -> next = previous -> next;
    previous -> next = temp;
    cout << "adding: " << countryName << " (prev: " << previous -> name << ")" << endl;
  }
}

/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
 void CountryNetwork::deleteCountry(string countryName)
 {
   Country *temp;
   Country *find = searchNetwork(countryName);
   if(find == nullptr)
   {
       cout << "Country does not exist." << endl;
   }
   if (head -> name == countryName)
   {
     temp = head;
     head = temp -> next;
     delete temp;
     temp = nullptr;
   }
   else
   {
     bool found = false;
     Country *last = head;
     temp = head -> next;
     while (!found && temp!=nullptr)
     {
       if (temp -> name == countryName)
       {
         found = true;
       }
       else
       {
         last = temp;
         temp = temp -> next;
       }
     }
     if (found)
     {
       if (temp -> next == nullptr)
       {
         last -> next = nullptr;
       }
       else
       {
         last -> next = temp -> next;
       }
       delete temp;
       temp = nullptr;
       last = nullptr;
     }
   }
 }


/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
  Country *last;
  deleteEntireNetwork();
  string defaultSetUp[6] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
  if (head == nullptr)
  {
    Country *temp = new Country;
    temp -> name = defaultSetUp[0];
    temp -> next = nullptr;
    head = temp;
    last = temp;
    cout << "adding: " << defaultSetUp[0] << " (HEAD)" << endl;

    for (int i = 1; i < 6; i++)
    {
      Country *temp = new Country;
      temp -> name = defaultSetUp[i];
      temp -> next = nullptr;
      last -> next = temp;
      cout << "adding: " << defaultSetUp[i] << " (prev: " << last -> name << ")" << endl;
      last = temp;
    }

  }

}



/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
  Country *returnCountry = nullptr;
  Country *temp = head;

  bool found = false;

  while (!found && temp != nullptr)
  {
    if(temp -> name == countryName)
    {
      found = true;
      returnCountry = temp;
    }
    else
    {
      temp = temp -> next;
    }
  }
  return returnCountry;
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
  Country *temp;
  temp = head;
  while (temp != nullptr)
  {
    cout << "deleting: " << temp -> name << endl;
    delete temp;
    temp = temp -> next;
  }

  head = nullptr;
}


/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
  Country *temp = head;

  if (head == nullptr)
  {
    cout << "Empty List" << endl;
  }
  while (temp -> name != receiver)
  {
    temp -> numberMessages += 1;
    temp -> message = message;
    cout << temp -> name << " [# messages received: " << temp -> numberMessages << "] received: " << temp -> message << endl;
    temp = temp -> next;
  }
  if (temp -> name == receiver)
  {
    temp -> numberMessages += 1;
    temp -> message = message;
    cout << temp -> name << " [# messages received: " << temp -> numberMessages << "] received: " << temp -> message << endl;
    cout << endl;
  }
}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
  if (head == nullptr)
  {
    cout << "== CURRENT PATH ==" << endl;
    cout << "nothing in path" << endl;
    cout << "===" << endl;
    cout << endl;
  }
  else
  {
    Country *temp = head;
    cout << "== CURRENT PATH ==" << endl;
    while (temp != nullptr)
    {
      cout << temp -> name << " -> ";
      temp = temp -> next;
    }
    cout << "NULL" << endl;
    cout << "===" << endl;
    cout << endl;
  }
}


/*
 * Purpose: reverse the entire network t
 * @param ptr head of list
 */
 void CountryNetwork::reverseEntireNetwork()
 {
   Country *temp, *temp2;
   temp = nullptr;

   while (head != nullptr)
   {
     temp2 = head -> next;
     head -> next = temp;
     temp = head;
     head = temp2;
   }
   head = temp;
 }
