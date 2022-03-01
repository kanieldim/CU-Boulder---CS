#include <string>
#include <iostream>
#include <cstring>
#include "heaps.hpp"

//rec10
//hw8

using namespace std;



//Purpose: perform all operations necessary to instantiate a class object
Heap :: Heap(int heapSize)
{
  this -> heapSize = heapSize;
  heap = new int[heapSize];
  currentSize = 0;
}

// Purpose: free all resources that the object has acquired
Heap :: ~Heap()
{
  delete [] heap;
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

bool aLessThanB(Heap *A, Heap *B)
{
  if (A < B)
  {
    return true;
  }
  else if (A > B)
  {
    return false;
  }
}

// Purpose: Print the heap array as it is.
void Heap :: printHeap()
{
  for (int i = 0; i < currentSize; i++)
  {
    cout << heap[i] << endl;
  }
}

// Purpose: enqueue new group into priority queue; call other
void Heap :: addToHeap(int value)
{
    if (currentSize == heapSize)
    {
      cout << "Heap full, cannot enqueue" << endl;
      return;
    }
    currentSize++;
    heap[currentSize - 1] = value;


    repairUpward(currentSize - 1);
}

//Purpose: remove the group (allocate the table) at the front of the priority queue from
int Heap :: removeFromHeap()
{
  if (isEmpty())
  {
    cout << "Heap empty, cannot dequeue" << endl;
  }
  else if (currentSize == 1)
  {
    currentSize--;
  }
  else
  {
    heap[0] = heap[currentSize - 1];
    repairDownward(0);
    currentSize--;
  }
  return heap[0];
}

// return: groupID of the group at the front of the priority queue
GroupNode Heap :: peekValue()
{
  if (isEmpty())
  {
    cout << "Heap empty, nothing to peek" << endl;
  }
  return heap[0];
}

//return: true if queue is full, false otherwise
bool Heap :: isFull()
{
  if (currentSize == heapSize)
  {
    return true;
  }
  return false;
}

// return: true if queue is empty, false otherwise
bool Heap :: isEmpty()
{
  if (currentSize == 0)
  {
    return true;
  }
  return false;
}

//Purpose: maintain heap properties by swapping node with parent if necessary
void Heap :: repairUpward(int nodeIndex)
{
  int p = parent(nodeIndex);

  while (p < nodeIndex)
  {
    if ( aLessThanB(heap[nodeIndex], heap[p]))
    {
        swap(heap[nodeIndex], heap[p]);
    }
    //nodeIndex--;

     //repairUpward(nodeIndex);
     nodeIndex = p;
    p = parent(nodeIndex);
  }
}

// Purpose: maintain heap properties by swapping node with child if necessary
void Heap :: repairDownward(int nodeIndex)
{
  int l = leftChild(nodeIndex);
  int r = rightChild(nodeIndex);
  int smallest = nodeIndex;

  if (l < currentSize && aLessThanB(heap[l], heap[nodeIndex]))
  {
    smallest = l;
  }
  if (r < currentSize && aLessThanB(heap[r], heap[smallest]))
  {
    smallest = r;
  }
  if (smallest != nodeIndex)
  {
    swap(heap[nodeIndex],heap[smallest]);
    repairDownward(smallest);
  }
}
