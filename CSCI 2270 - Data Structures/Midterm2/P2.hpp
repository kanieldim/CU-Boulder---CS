#include <iostream>
#include <string>

using namespace std;

struct node{
  int key;
  struct node* next;
};

class HashTable {
  int tableSize;
  node* *table;
  node* createNode(int ket, node* next);

public:
    HashTable(int hashTableSize);
    ~HashTable();
    bool isInTable(int key);
    bool isSubset(int arr1[], int arr2[]);
    void insertItem(int key);
    unsigned int hashFunction(int key);
    void printTable();
    node* searchTable(int key);

};
