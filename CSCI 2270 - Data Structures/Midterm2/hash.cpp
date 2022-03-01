// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"

//rec9
//HW7

using namespace std;

node* HashTable::createNode(int key)
{
    node* nw = new node;
    nw->data = key;
    nw->next = NULL;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    hashTable = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        hashTable[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    // mod always return positive
    if (key < 0)
    {
      int q = -(key / tableSize);
      key += (q+1) * tableSize;
    }

    return (key % tableSize);
}

// TODO Complete this function
//function to search
node* HashTable::searchItem(int key)
{
    //Compute the index by using the hash function

    int index = hashFunction(key);
    node *temp = hashTable[index];
    while (temp != nullptr)
    {
      if (temp -> data == key)
      {
        return temp;
      }
        temp = temp -> next;
    }
    return nullptr;


    //TODO: Search the list at that specific index and return the node if found
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key)
{
    if(!searchItem(key))
    {
      int index = hashFunction(key);
      node *newNode = new node;
      newNode->data=key;
      newNode->next = NULL;
      if(hashTable[index] == NULL)//if there is no element
      {
        hashTable[index] = newNode;//insertion at head
        return true;
      }
      else //collisions
      {

        newNode -> next = hashTable[index];//inserting at the head;
        hashTable[index] = newNode;
        return true;
      }
    }
    return false;
}

//TODO Complete this function
// function to display hash table
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        node *temp = hashTable[i];
        cout << i <<"|| ";
        while (temp != nullptr)
        {

          cout << " -> " << temp -> data;
          temp = temp -> next;
        }
        cout << endl;
        //TODO
    }

 }

 // int main(){
 //   cout << "success"<<endl;
 // }
