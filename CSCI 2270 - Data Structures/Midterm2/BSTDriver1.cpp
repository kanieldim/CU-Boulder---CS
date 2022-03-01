#include <iostream>
#include <string>
#include "BST.hpp"
#define COUNT 10

using namespace std;

//rec8
//hw5
//HW6

Node* BST:: createNode(int data)
{
    Node* newNode = new Node;
    newNode->key = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* BST :: addNodeHelper(Node* currNode, int data)
{
  if(currNode == nullptr){
        return createNode(data);
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data){
        currNode->left = addNodeHelper(currNode->left,data);
    }
    return currNode;
}


void BST :: addNode(int data)
{
  addNodeHelper(root, data);
  cout<<data<<" has been added"<<endl;
}

// Node* BST :: deleteNodeHelper(Node* currNode, int value)
// {
//
// }

Node* BST :: searchKeyHelper(Node* currNode, int data)
{
  if(currNode == nullptr)
        return nullptr;

    if(currNode->key == data)
        return currNode;

    if(currNode->key > data)
        return searchKeyHelper(currNode->left, data);

    return searchKeyHelper (currNode->right, data);
}

bool BST :: searchKey(int data)
{
  Node* tree = searchKeyHelper(root, data);
    if(tree != nullptr) {
        return true;
    }
    cout<<"Key not present in the tree"<<endl;
    return false;
}

void BST :: printTreeHelperLeft(Node* currNode)
{
  if(currNode)
  {
    printTreeHelperLeft( currNode->left);
    cout << " "<< currNode->key;
  }

       //cout << " "<< currNode->key;

        //printTreeHelper( currNode->right);
        //cout << " "<< currNode->key;

}

void BST :: printTreeHelperRight(Node* currNode)
{

  if(currNode)
  {
    cout << " "<< currNode->key;
    printTreeHelperRight( currNode->right);
  }
}


void BST :: printTree()
{
  printTreeHelperLeft(root);
  printTreeHelperRight(root);
  cout<<endl;
}


// void BST::deleteNode(Node *currNode, int value)
// {
//   if(currNode == nullptr)
//   {
//     return nullptr;
//   }
//   else if(value < currNode->key)
//   {
//     currNode->left = deleteNode(currNode->left, value);
//   }
//   else if(value > currNode->key)
//   {
//     currNode->right = deleteNode(currNode->right, value);
//   }
//   // We found the node with the value
//   else
//   {
//     //TODO Case : No child
//     if(currNode->left == nullptr && currNode->right == nullptr)
//     {
//       delete currNode;
//       return nullptr;
//     }
//     //TODO Case : Only right child
//     else if(currNode->left == NULL)
//     {
//       // replace with the child and delete it
//       Node *temp = currNode -> right;
//       //currNode -> key = temp -> key;
//
//       delete currNode;
//       return temp;
//
//     }
//     //TODO Case : Only left child
//     else if(currNode->right == nullptr)
//     {
//       Node *temp = currNode -> left;
//       delete currNode;
//       return temp;
//     }
//     //TODO Case: Both left and right child
//     else
//     {
//       ///Replace with Minimum from right subtree
//       // find min of right subtree of currNode
//       Node* min = getMinValueNode(currNode -> right);
//       currNode->key = min->key;
//       currNode -> right = deleteNode(currNode -> right, min->key);
//     }
//   }
// }




BST :: BST()
{
  root = nullptr;
}

BST::BST(int data)
{
    root = createNode(data);
    cout<< "New tree created with "<<data<<endl;
}

BST :: ~BST()
{

}

void BST::print2DUtilHelper(Node *currNode, int space)
{
    // Base case
    if (currNode == nullptr)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtilHelper(currNode->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", currNode->key);

    // Process left child
    print2DUtilHelper(currNode->left, space);
}

void BST :: print2DUtil (int space)
{
  print2DUtilHelper(root, space);
}
