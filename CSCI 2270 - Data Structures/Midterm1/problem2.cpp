#include <iostream>

using namespace std;

/* *********** IMPORTANT NOTE ************
  Same with this problem.
  So when I use the command prompt with this code,
  it doesn't seem to work but when I use this same code
  on AWS cloud9, it works completely fine and I
  couldn't find out the reason why it doesn't work on
  command prompt (window powershell)
*/


struct Node
{
  int key;
  Node *next;
};


void print(Node *head)
{
  Node *temp = head;
  Node *temp2 = head;
  int oddNumber = -1;
  int evenNumber = -1;

  cout << "Odd Number list: " << endl;
  while (temp != nullptr)
  {
    if (temp -> key % 2 == 1)
    {
      oddNumber = temp -> key;
      cout << oddNumber << endl;
      temp = temp -> next;
    }
    else if (temp -> key % 2 != 1)
    {
      temp = temp -> next;
    }
  }
  if (oddNumber == -1)
  {
    cout << "None" << endl;
  }

  cout << "Even Number list: " << endl;
  while (temp2 != nullptr)
  {
    if ((temp2 -> key)%2 == 0)
    {
      evenNumber = temp2 -> key;
      cout << evenNumber << endl;
      temp2 = temp2 -> next;
    }
    else
    {
      temp2 = temp2 -> next;
    }
  }
  if (evenNumber == -1)
  {
    cout << "None" << endl;
  }

}



int main(int argc, char const *argv[])
{
  // ------------- CASE 1 -------------
  Node *n1 = new Node;
  Node *n2 = new Node; n1 -> next = n2;
  Node *n3 = new Node; n2 -> next = n3;
  Node *n4 = new Node; n3 -> next = n4;

  n1 -> key = 1;
  n2 -> key = 2;
  n3 -> key = 3;
  n4 -> key = 4;

  print(n1);
  /*
  result:
    Odd number list:
    1
    3
    Even Number list:
    2
    4
  */

  return 0;

  // ------------- CASE 2 -------------
  // Node *n1 = new Node;
  // Node *n2 = new Node; n1 -> next = n2;
  // Node *n3 = new Node; n2 -> next = n3;
  // Node *n4 = new Node; n3 -> next = n4;
  // Node *n5 = new Node; n4 -> next = n5;
  //
  // n1 -> key = 3;
  // n2 -> key = 6;
  // n3 -> key = 10;
  // n4 -> key = 5;
  // n5 -> key = 9;
  //
  // print(n1);
  //   /*
  // result:
  //   Odd number list:
  //   3
  //   5
  //   9
  //   Even Number list:
  //   6
  //   10
  // */
  //
  // return 0;

  // ------------- CASE 3 -------------

  // Node *n1 = new Node;
  // Node *n2 = new Node; n1 -> next = n2;
  // Node *n3 = new Node; n2 -> next = n3;
  // Node *n4 = new Node; n3 -> next = n4;
  //
  // n1 -> key = 1;
  // n2 -> key = 3;
  // n3 -> key = 5;
  // n4 -> key = 7;
  //
  // print(n1);
  // /*
  // result:
  //   Odd number list:
  //   1
  //   3
  //   5
  //   7
  //   Even Number list:
  //   None
  // */
  //
  //
  // return 0;

  // ------------- CASE 4 -------------

  // Node *n1 = new Node;
  // Node *n2 = new Node; n1 -> next = n2;
  // Node *n3 = new Node; n2 -> next = n3;
  // Node *n4 = new Node; n3 -> next = n4;
  //
  // n1 -> key = 2;
  // n2 -> key = 4;
  // n3 -> key = 6;
  // n4 -> key = 8;
  //
  // print(n1);
  //
  // /*
  // result:
  //   Odd number list:
  //   None
  //   Even Number list:
  //   2
  //   4
  //   6
  //   8
  // */
  //
  // return 0;

}
