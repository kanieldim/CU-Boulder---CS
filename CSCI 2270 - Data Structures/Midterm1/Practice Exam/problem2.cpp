#include <iostream>

using namespace std;


struct Node
{
  int key
  Node *next;
};

Node *deleteNegatives (Node *head)
{
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
