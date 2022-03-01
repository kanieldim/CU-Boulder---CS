#include <iostream>

using namespace std;


struct Node
{
  int key;
  Node *next;
};

Node *deleteNegatives (Node *head)
{
  // if(!head) same
  if (head == nullptr)
  {
    cout << "Linked list is empty" << endl;
  }
  Node *temp = head;
  Node *temp2 = head -> next;

  if (head -> key < 0)
  {
    temp = head;
    head = head -> next;
    delete temp;
    temp = nullptr;
  }
  else
  {
    Node *temp2 = head;
    while (temp2 -> next != nullptr)
    {
      temp = temp2;
      temp2 = temp2 -> next;
      if (temp2 -> key < 0)
      {
        if (temp2 -> next == nullptr)
        {
          temp -> next = nullptr;
          delete temp2;
          temp2 = nullptr;
        }
        else // temp2 -> next != nullptr
        {
          temp -> next = temp2 -> next;
          delete temp2;
          temp2 = nullptr;
        }
      }
    }
  }
  return head;
}


int main(int argc, char const *argv[])
{
  Node *n1 = new Node;
  Node *n2 = new Node; n1 -> next = n2;
  Node *n3 = new Node; n2 -> next = n3;
  Node *n4 = new Node; n3 -> next = n4;
  Node *n5 = new Node; n4 -> next = n5;

  n1 -> key = -3;
  n2 -> key = 5;
  n3 -> key = -7;
  n4 -> key = 8;
  n5 -> key = -9;

  Node *result;
  result = deleteNegatives(n1);

  // string isEven = lengthIsEven(n1) ? "true" : "false";
  // if (lengthIsEven(n1))
  // {
  //   isEven = "true";
  // }
  // else
  // {
  //   isEven = "false";
  // }

  cout << "Head: " << result->key << endl;



  return 0;
}
