/*
Implement a isSubset function that checks if all elements of arr2 are in arr1
bool isSubset(int arr1[], int arr2[]) // example declaration
You can assume that there are distinct elements in the array.
Hint: You can use hashtables to check if elements from a list exist in the
other
*/

/*
Implementation:
store all elements of array one into a hash table.
use an isInTable function and iterate through array two. If it is found in the table, continue until the end of the array is reached.
if it is not found, return false.
*/

#include<iostream>
#include "P2.hpp"

using namespace std;

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

HashTable::~HashTable(){
   delete table;
}


node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;

}

unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

void HashTable::insertItem(int key)
{
     int index = hashFunction(key); //find the index
   node *temp = table[index];
  node *ptr = createNode(key,temp);
          if(!searchTable(key))
          {


            if (temp != NULL){
                while (temp -> next != NULL){
                    temp = temp -> next;
                }
                temp-> next = ptr;
            }

           else{
              table[index] = ptr;
              ptr-> next = NULL;
              delete temp;
            }
            }

            else{
                cout << "duplicate entry: " << key << endl;
                return;
            }

  return;

}



bool HashTable::isInTable(int key){


    node *temp = searchTable(key);
    if (temp == nullptr){
        //delete temp;
      return false;
    }
    else{
        //delete temp;
      return true;
    }

}
node* HashTable::searchTable(int key){

    //cout<< "10";
      int index = hashFunction(key);

      if (table[index] != nullptr){
        node *temp = table[index];
        while (temp != nullptr){
          if (temp -> key == key){
            return temp;
          }
          else{
            temp = temp -> next;
          }
        }

      }


    return nullptr;
}

bool HashTable::isSubset(int arr1[], int arr2[]){

  int k=0;
  while (isdigit(arr2[k])){
    k++;
  }
  for(int i = 0; i< k ; i++){
      if(isInTable(arr2[i]) == false){
        return false;
      }
  }
  return true;
}

void HashTable::printTable()
{

  //cout<< "sdihfdsihsidfoies";
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";
            while (table[i] != NULL){
              cout << table[i] -> key<< "---->";
              table[i] = table[i] -> next;
            }
            cout<< endl;
 }
}
