#include <iostream>
#include "hash.hpp"

using namespace std;



int main()
{
  int a[] = {-1, 1};
  //int a[] = {-1,0,1};
  //int a[] = {-4,-5,-1,0,35,27};
  int n = 7;

    // 7 is count of buckets in hash table
  HashTable ht(7);

    // insert the keys into the hash table.
    // SILVER TODO : Complete insertItem() function
    for (int i = 0; i < n; i++)
    {
        ht.insertItem(a[i]);
    }

    ht.printTable();

    cout << "success" << endl;



  return 0;
}
