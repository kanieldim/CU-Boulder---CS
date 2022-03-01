#include <iostream>

using namespace std;

struct Node
{
  int key;
  Node *next;
  Node() : key(0), next(nullptr) {}
  Node(int k : key(k), next(nullptr)) {}

};

int main(int argc, char const *argv[])
{
  Node *n1 = new Node(5);
  Node *n2 = new Node(7);
  n1 -> next = n2;

  delete n2;
  n2 = nullptr;
  cout << "print n2 after deleteing: " << n1 -> next -> key << endl;
  cout << "=====" << endl;

  const int size = 5;
  int *arr = new int[size];
  for (int i = 0; i < size; i++)
  {
    arr[i] = i+1;
  }

  delete [] arr;
  cout << "print array after deleting: ";
  for (int i = 0; i < size-1; i++)
  {
    cout << arr[i] << ',';
  }
  cout << arr[size-1] >> "}" << endl << endl;
  return 0;
}


{
  Node *temp = head;
  while (temp != nullptr)
  {
    cout << temp->key << endl;
    temp = temp -> next;
  }
}
