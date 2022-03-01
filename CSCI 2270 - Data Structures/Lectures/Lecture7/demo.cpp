// Today:
//   Finish class with multi-file compilation example with Time12 class
//   The node structure
//   linked list
//     sample LL
//     LL class
//
//
//   Multi-file
//     Time12Driver.cpp, Time12.cpp
//     command line $ g++ Time12.cpp
//       needs Driver.cpp
//     command line $ g++ -c Time12.cpp
//       creates object file -o
//     command line $ g++ Time12.o Time12Driver.o -o Time12program.exe
//       create object file and then combine
//     command line $ g++ Time12.cpp Time12Driver.cpp
//       what we learned before

Motivation:
  say we have an array with 1000 of its elements populated (Length 1001)
  The array is sorted,
    [1,3,4,7,12,...450]
      n = 1001
    We want to insert an element, and keep array sorted
      New element has a value = 2;
      How many memory copy operations do we have to perform?
        1000 memory tranfers
        1000 ! = very inefficient

The linked list node
  struct Node
  {
    string key;
    Node *next; // self referential pointer
                // point to its own type

  };

  Recall that can have a pointer to a struct type:
    Node *p1;

  int main()
  {
    Node *p1 = new Node; // dynamically allocated Node to pointer p1
    Node *p2 = new Node; // dynamically allocated Node to pointer p2

    p1 -> key = "llama";
    p2 -> key = "donkey";

    p1 -> next = p2;
    p2 = new Node;
    cout << p1->next->key << endl;
    // result: donkey
    // link up B(p2) and C
      // p1->next->next = p2
  }

  nodes only knows about next node

  head and tail
  tail: next = null

  want to insert
  insert value = 2

  The linked list class
    - Define a struct for Node (singly linked)
      - two members
          1. key
          2. self ref. pointer
    - Define SLL class
      - private data members:
          1. head
          2. tail
      - public functions:
          constructor
            - no parameters
            - set pointers to null
          destructor
            - gets called when object goes out of scope
            - use it to de-allocated all the linked nodes

      - Node* search (string skey)
        - locate a node with gien value
        - return pointer
      - void appendNode(string newItem)
        - add new node to the end (tail)
      - void insert(string afterMe, string newItem)
      - void displayList()
        - start at head
        - traverse list and display every node key

struct Node
{
  string key;
  Node *next;
};

class SLL
{
private:
  Node *head, *tail;
public:
  SLL(); // constructor
  ~SLL(); // destructor

  Node * search(string sKey)
  // precondition: sKey parametr is a string type

  // post condition: if found, returns pointer to the
  // node conatining sKey otherwise, returns nullptr

}
