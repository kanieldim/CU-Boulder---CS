#include <iostream>
using namespace std;

#include "binaryST.h"

int main(){
	BinaryST bst0;

	bst0.insert( 9 );
	bst0.insert( 10 );
	bst0.insert( 2 );
	bst0.insert( 10 );
	bst0.insert( 7 );
	bst0.insert( 1 );

/*  
        9
       /  \ 
      2   10
     / \    \
    1   7   10
*/

	cout << "display in-order: " << endl;
	bst0.disp("in-order");

	Node *sNode = bst0.search(2);
	cout << "skey: " << sNode->key << endl;


	return 0;
}

// 9,2,15,1,7        del(1)
// 9,2,15,1,7,8      del(2)
// 9,2,15,1,7,8,5,6  del(2), del(5), del(root = 9)
// 9,5,3 			 del(5)
// 9,2,5,3,6 		 del(2)
