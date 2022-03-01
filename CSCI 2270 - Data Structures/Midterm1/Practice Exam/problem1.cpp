#include <iostream>

using namespace std;

struct Node
{
  int key;
  Node *next = nullptr;
};

bool lengthIsEven(Node *head)
{
  int count = 0;
  Node *temp = head;

  if (head == nullptr) // case list i empty
  {
    return true;
  }

  while (temp != nullptr)
  {
    temp = temp -> next;
    count++;
  }

  if (count%2 == 0)
  {
    return true;
  }
  else
  {
    return false;
  }

}

int main(int argc, char const *argv[])
{
  Node *n1 = new Node;
  Node *n2 = new Node; n1 -> next = n2;
  Node *n3 = new Node; n2 -> next = n3;
  Node *n4 = new Node; n3 -> next = n4;
  Node *n5 = new Node; n4 -> next = n5;

  n1 -> key = 4;
  n2 -> key = 6;
  n3 -> key = 1;
  n4 -> key = 8;
  n5 -> key = 3;

  string isEven = lengthIsEven(n1) ? "true" : "false";
  if (lengthIsEven(n1))
  {
    isEven = "true";
  }
  else
  {
    isEven = "false";
  }

  cout << "List has even number of elts? " << isEven << endl;



  return 0;
}
