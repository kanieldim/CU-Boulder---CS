#include <string>
#include <iostream>
#include <cstring>
#include "PriorityQueue.hpp"

using namespace std;

//Purpose: perform all operations necessary to instantiate a class object
PriorityQueue :: PriorityQueue(int queueSize)
{
  this -> maxQueueSize = queueSize;
  priorityQueue = new GroupNode*[maxQueueSize];
  currentQueueSize = 0;
}

// Purpose: free all resources that the object has acquired
PriorityQueue :: ~PriorityQueue()
{
  delete [] priorityQueue;
}

/*
Finds the parent of a node, given its index.
*/
int parent(int index)
{
  return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int rightChild(int index)
{
  return ((2*index) + 2);
}

bool aLessThanB(GroupNode A, GroupNode B)
{
  if (A.groupSize < B.groupSize)
  {
    return true;
  }
  else if (A.groupSize > B.groupSize)
  {
    return false;
  }
  else if (A.groupSize == B.groupSize)// if A == B
  {
    if (A.cookingTime < B.cookingTime)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

// Purpose: enqueue new group into priority queue; call other
void PriorityQueue :: enqueue(string _groupName, int _groupSize, int _cookingTime)
{
    if (currentQueueSize == maxQueueSize)
    {
      cout << "Heap full, cannot enqueue" << endl;
      return;
    }
    currentQueueSize++;
    priorityQueue[currentQueueSize - 1].groupName = _groupName;
    priorityQueue[currentQueueSize - 1].groupSize = _groupSize;
    priorityQueue[currentQueueSize - 1].cookingTime = _cookingTime;

    repairUpward(currentQueueSize - 1);
}

//Purpose: remove the group (allocate the table) at the front of the priority queue from
void PriorityQueue :: dequeue()
{
  if (isEmpty())
  {
    cout << "Heap empty, cannot dequeue" << endl;
  }
  else if (currentQueueSize == 1)
  {
    currentQueueSize--;
  }
  else
  {
    priorityQueue[0] = priorityQueue[currentQueueSize - 1];
    repairDownward(0);
    currentQueueSize--;
  }
}

// return: groupID of the group at the front of the priority queue
GroupNode PriorityQueue :: peek()
{
  if (isEmpty())
  {
    cout << "Heap empty, nothing to peek" << endl;
  }
  return priorityQueue[0];
}

//return: true if queue is full, false otherwise
bool PriorityQueue :: isFull()
{
  if (currentQueueSize == maxQueueSize)
  {
    return true;
  }
  return false;
}

// return: true if queue is empty, false otherwise
bool PriorityQueue :: isEmpty()
{
  if (currentQueueSize == 0)
  {
    return true;
  }
  return false;
}

//Purpose: maintain heap properties by swapping node with parent if necessary
void PriorityQueue :: repairUpward(int nodeIndex)
{
  int p = parent(nodeIndex);

  while (p < nodeIndex)
  {
    if ( aLessThanB(priorityQueue[nodeIndex], priorityQueue[p]))
    {
        swap(priorityQueue[nodeIndex], priorityQueue[p]);
    }
    //nodeIndex--;

     //repairUpward(nodeIndex);
     nodeIndex = p;
    p = parent(nodeIndex);
  }
}

// Purpose: maintain heap properties by swapping node with child if necessary
void PriorityQueue :: repairDownward(int nodeIndex)
{
  int l = leftChild(nodeIndex);
  int r = rightChild(nodeIndex);
  int smallest = nodeIndex;

  if (l < currentQueueSize && aLessThanB(priorityQueue[l], priorityQueue[nodeIndex]))
  {
    smallest = l;
  }
  if (r < currentQueueSize && aLessThanB(priorityQueue[r], priorityQueue[smallest]))
  {
    smallest = r;
  }
  if (smallest != nodeIndex)
  {
    swap(priorityQueue[nodeIndex],priorityQueue[smallest]);
    repairDownward(smallest);
  }
}
