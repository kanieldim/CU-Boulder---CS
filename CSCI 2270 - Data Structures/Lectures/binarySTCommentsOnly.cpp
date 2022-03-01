#include <iostream>
using namespace std;

#include "binaryST.h"

BinaryST::BinaryST()
{
	root = nullptr;
}

// Insert new node
void BinaryST::insert( int newValue )
{	
	// create a pointer to keep track of previous node
	Node *prev = nullptr;

	// pointer for traversing the tree. Start with Root.
	Node *temp = root;

	// create a new node
	Node *n = new Node;

	// Set all pointers inside n to null. Write new value to key.

	n->parent = nullptr;
	n->leftChild = nullptr;
	n->rightChild = nullptr;
	n->key = newValue;

	// Loop until we find first empty spot in tree
	// If tree is empty, root is null and loop will not run

	while( temp != nullptr ){
		//set prev to temp keep track of last node
		prev = temp;

		// check which way to look for empty spot
		if( n->key < temp->key )
			temp = temp->leftChild;
		else // if n->key is greater than or equal to
			temp = temp->rightChild;
	}

	// at this point the parent has been found

	if( prev == nullptr)
		root = n;
	else if(n->key < prev->key){
		prev->leftChild = n;
		n->parent = prev;
	}
	else{
		prev->rightChild = n;
		n->parent = prev;
	}







}

void BinaryST::disp( string Order )
{
	if(Order == "pre-order")
		dispPreOrd(root);
	else if(Order == "in-order")
		dispInOrd(root);

}

void BinaryST::dispPreOrd( Node *n )
{

}

void BinaryST::dispInOrd( Node *n )
{
	if(n->leftChild != nullptr)
		dispInOrd(n->leftChild);

	cout << n->key << endl;
	
	if(n->rightChild != nullptr)
		dispInOrd(n->rightChild);

}

Node* BinaryST::search( int value )
{
	return searchRecur(root,value);
}

Node* BinaryST::searchRecur( Node *n , int searchKey )
{
	cout << "node visited: " << n->key << endl;
	if(n != nullptr){
		if( n->key == searchKey )
			return n;
		else if( n->key > searchKey )
			return searchRecur(n->leftChild,searchKey);
		else
			return searchRecur(n->rightChild,searchKey);
	}
	else
		return nullptr;
}

Node* BinaryST::findMin()
{
	return getMin(root);
}

Node* BinaryST::getMin( Node *n )
{
	while(n->leftChild!=nullptr)
		n = n->leftChild;
	return n;

}


void BinaryST::deleteNode( int value )
{
	Node *n = search(value);
	
	// Non-root case
	if( n != root){
		// I) The Leaf Case (n is a leaf node)

			// Need to go up to the parent node, and update the
			// correct child pointer
			// Check n's relationship to its parents
			// is n the left child?


			// otherwise, n must be the right child


		
		// II) The 2-children case

			// find the min of the right sub-tree to replace
			// the deleted node

			// if min IS the right child of n

				// make parent point to the min
				// check if node is left child


				//otherwise it is a right child



				// make min point to the parent

				// make min point to n's old child

				// make old LC point to min

			
			// otherwise, min is NOT the RC of n
			// meaning it's somewhere in the right subtree

				// min'old RC takes min's spot

				// set 

				// new node needs to point back up to min's former
				// parent



				// now, insert min into n's old spot
				// check if node is LC


				// otherwise, it is the RC




		// III) The one child case 



	}
	//Root case
	else{}

	delete n;

}



