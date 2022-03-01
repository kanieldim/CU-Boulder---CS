#include <iostream>
#include "MovieTree.hpp"

using namespace std;

MovieTree :: MovieTree()
{
  root = nullptr;
}

void deleteAll(TreeNode* node)
{
    if (!node)
    {
        return;
    }
    while (node -> head != nullptr)
    {
        delete node -> head;
        node -> head = node -> head -> next;
    }
    delete node -> head;
    deleteAll(node->leftChild);
    deleteAll(node->rightChild);


    delete node;

    node = nullptr;
}

MovieTree :: ~MovieTree()
{
  deleteAll(root);
}



void printLinkedHelper(LLMovieNode *temp)
{
  while (temp != nullptr)
  {
    cout << " >> " << temp -> title << " " << temp ->rating << endl;
    temp = temp -> next;
  }
}

void printTreeHelper(TreeNode *node)
{
  if (node)
  {
    printTreeHelper(node -> leftChild);
    cout << "Movies starting with letter: " << node -> titleChar << endl;
    printLinkedHelper(node -> head);
    printTreeHelper(node -> rightChild);
  }
}

void MovieTree :: printMovieInventory()
{
  if (root != nullptr)
  {
    printTreeHelper(root);
  }
}
TreeNode* createNode(char titleChar)
{
    TreeNode* newNode = new TreeNode;
    newNode -> titleChar = titleChar;
    newNode -> leftChild = nullptr;
    newNode -> rightChild = nullptr;
    return newNode;
}


TreeNode* addTreeNodeHelper(TreeNode* currNode, char titleChar)
{
    if(currNode == nullptr)
    {
        return createNode(titleChar);
    }
    else if(currNode -> titleChar < titleChar)
    {
        currNode -> rightChild = addTreeNodeHelper(currNode -> rightChild, titleChar);
    }
    else if(currNode -> titleChar > titleChar)
    {
        currNode -> leftChild = addTreeNodeHelper(currNode -> leftChild, titleChar);
    }
    return currNode;

}



void MovieTree :: addMovie(int ranking, string title, int year, float rating)
{
  if (root == nullptr)
  {
    root = addTreeNodeHelper(root, title[0]);
    root -> head = new LLMovieNode(ranking, title, year, rating);
    return;
  }

  TreeNode *temp = root;
  bool found = false;
  while(!found && temp != nullptr)
  {
    if (temp -> titleChar > title[0])
    {
      temp = temp -> leftChild;
    }
    else if (temp -> titleChar < title[0])
    {
      temp = temp -> rightChild;
    }
    else if (temp -> titleChar == title[0])
    {
      found = true;
      LLMovieNode* currNode = temp -> head;
      LLMovieNode* newNode = new LLMovieNode(ranking, title, year, rating);
        if (temp -> head -> title > title)
      {
        newNode -> next = temp -> head;
        temp -> head = newNode;
        return;

      }
      while (currNode -> next != nullptr && currNode -> next -> title < title)
      {
         currNode = currNode -> next;
      }
      newNode -> next = currNode -> next;
      currNode -> next = newNode;
    }
  }
  if (found == false)
  {
    addTreeNodeHelper(root, title[0]);
    temp = root;

    while(temp != nullptr)
    {
      if (temp -> titleChar > title[0])
      {
        temp = temp -> leftChild;
      }
      else if (temp -> titleChar < title[0])
      {
        temp = temp -> rightChild;
      }
      else if (temp -> titleChar == title[0])
      {
        LLMovieNode* currNode = temp -> head;
        LLMovieNode* newNode = new LLMovieNode(ranking, title, year, rating);

        if (temp -> head == nullptr)
        {
          temp -> head = newNode;
            return;
        }

        while (currNode -> next != nullptr && currNode -> next -> title < title)
        {
           currNode = currNode -> next;
        }
        newNode -> next = currNode -> next;
        currNode -> next = newNode;
        return;
      }
    }
  }
}

TreeNode* getLastAlphabet(TreeNode* currNode)
{
    if(currNode -> rightChild == nullptr)
    {
      return currNode;
    }
    return getLastAlphabet(currNode -> rightChild);
}

TreeNode* getFirstAlphabet(TreeNode* currNode)
{
    if(currNode -> leftChild == nullptr)
    {
      return currNode;
    }
    return getFirstAlphabet(currNode -> leftChild);
}


TreeNode* deleteTreeNode(TreeNode *currNode, char titleChar)
{

  if(currNode == nullptr)
  {
    return nullptr;
  }
  else if(titleChar < currNode -> titleChar)
  {
    currNode-> leftChild = deleteTreeNode(currNode -> leftChild, titleChar);
  }
  else if(titleChar > currNode -> titleChar)
  {
    currNode -> rightChild = deleteTreeNode(currNode -> rightChild, titleChar);
  }
  // We found the node with the value
  else
  {
    //TODO Case : No child
    if(currNode -> leftChild == nullptr && currNode -> rightChild == nullptr)
    {
      delete currNode;
      return nullptr;
    }
    //TODO Case : Only right child
    else if(currNode -> leftChild == nullptr)
    {
      // replace with the child and delete it
      TreeNode *temp = currNode -> rightChild;
      //currNode -> key = temp -> key;

      delete currNode;
      return temp;
    }
    //TODO Case : Only left child
    else if(currNode->rightChild == nullptr)
    {
      TreeNode *temp = currNode -> leftChild;
      delete currNode;
      return temp;
    }
    //TODO Case: Both left and right child
    else
    {
      ///Replace with Minimum from right subtree
      // find min of right subtree of currNode
      TreeNode* last = getFirstAlphabet(currNode -> rightChild);
      currNode -> titleChar = last -> titleChar;
      currNode -> head = last -> head;
      currNode -> rightChild = deleteTreeNode(currNode -> rightChild, last -> titleChar);
    }

  }
  return currNode;
}

void MovieTree :: deleteMovie(string title)
{
  TreeNode *temp;
  temp = root;
  bool trueOrFalse = false;
  bool found;
  while(temp != nullptr)
  {
      if (temp -> titleChar > title[0])
      {
          temp = temp ->leftChild;
      }
      else if (temp -> titleChar < title[0])
      {
          temp = temp -> rightChild;
      }
      else if (temp -> titleChar == title[0])
      {
          if (temp -> head -> title == title)
          {
            found = true;
            LLMovieNode *temp2 = temp -> head;
            temp -> head = temp2 -> next;
            delete temp2;
            temp2 = nullptr;
            if (temp -> head == nullptr)
            {
              root = deleteTreeNode(root, temp -> titleChar);

            }
            return;
          }
          else
          {
            LLMovieNode *temp2 = temp -> head;
            LLMovieNode *temp3 = temp -> head -> next;
            while (!found && temp3 != nullptr)
            {
              if (temp3 -> title == title)
              {
                found = true;
              }
              else
              {
                temp2 = temp3;
                temp3 = temp3 -> next;
              }
            }
            if (found)
            {
              if (temp3 -> next == nullptr)
              {
                temp2 -> next = nullptr;
              }
              else
              {
                temp2 -> next = temp3 -> next;
              }
              delete temp3;
              temp3 = nullptr;
              temp2 = nullptr;
              if (temp -> head == nullptr)
              {
                root = deleteTreeNode(root, temp -> titleChar);

              }
              return;
            }
          }

      }
    }
    if (found == false)
    {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
    }
}
