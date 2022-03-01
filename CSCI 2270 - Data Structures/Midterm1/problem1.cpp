#include <iostream>

using namespace std;

/* *********** IMPORTANT NOTE ************
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


int sumEvens(Node *head)
{
  Node *temp = head;
  int result = 0;
  int even = 0;
  if (head == nullptr)
  {
    return 0;
  }
  else
  {
    while (temp != nullptr)
    {
      even = temp -> key;
      if (even%2 == 0)
      {
        result = result + even;
        temp = temp -> next;
      }
      else
      {
        temp = temp -> next;
      }
    }
  }
  return result;
}



int main(int argc, char const *argv[])
{
  // ------------- CASE 1 -------------
  int realResult;
  Node *n1 = new Node;
  Node *n2 = new Node; n1 -> next = n2;
  Node *n3 = new Node; n2 -> next = n3;
  Node *n4 = new Node; n3 -> next = n4;

  n1 -> key = 1;
  n2 -> key = 2;
  n3 -> key = 3;
  n4 -> key = 4;


  realResult = sumEvens(n1);

  cout << realResult << endl;
  // Result : 6

  return realResult;

  // ------------- CASE 2 -------------
  // int realResult;
  // Node *n1 = new Node;

  // realResult = sumEvens(n1);
  //
  // cout << realResult << endl;
  // // Result : 0
  // return realResult;

  // ------------- CASE 3 -------------

  // int realResult;
  // Node *n1 = new Node;
  // Node *n2 = new Node; n1 -> next = n2;
  // Node *n3 = new Node; n2 -> next = n3;
  // Node *n4 = new Node; n3 -> next = n4;
  //
  // n1 -> key = 8;
  // n2 -> key = 3;
  // n3 -> key = 9;
  // n4 -> key = 9;
  //
  //
  // realResult = sumEvens(n1);
  //
  // cout << realResult << endl;
  // // Result : 8
  // return realResult;



}
