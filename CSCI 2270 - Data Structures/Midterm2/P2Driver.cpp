#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include "P2.hpp"

using namespace std;
int main(){
  int a1[] ={1,2,3,4,5};
  int a2[] ={2,3,1};
  int size = 0;
  int i=0;
size = *(&a1 + 1) - a1;
  HashTable ht(size);


cout<< "the size is "<< size<< endl;

  for(int i=0; i< size; i++){
    int key = a1[i];
      ht.insertItem(key);
      //add all contents of the first array in a table.
  }
//cout<< "1";
    cout<< "Contents of the hash table from the values in array 1 are"<<endl;
    ht.printTable();
  //  cout<< "2";

    int k = 0;
    k= *(&a2 +1) - a2;

    cout<< "array 2 contains: [";
    for (int i=0; i<k;i++){
      cout<< a2[i]<< ",";
    //  cout<< "3";
    }
    cout<< "]"<< endl;

    cout<< "is subset? ";
    //cout<< "4";
    if(ht.isSubset(a1,a2)== false){
      cout<< "false"<< endl;

    }
    if(ht.isSubset(a1,a2)==true){
      cout<< "true"<< endl;
    }

//cout<< "5";
}
