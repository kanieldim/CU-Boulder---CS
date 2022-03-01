#include "ProducerConsumer.hpp"

#include <iostream>

using namespace std;

ProducerConsumer :: ProducerConsumer()
{
  queueFront = -1;
  queueEnd = -1;
}

bool ProducerConsumer :: isEmpty()
{
  if (queueFront == -1 || queueEnd == -1)
  {
    return true;
  }
  return false;
}

bool ProducerConsumer :: isFull()
{
  if ((queueEnd+1)%SIZE == queueFront)
  {
    return true;
  }
  return false;
}

void ProducerConsumer :: enqueue (string player)
{
  if (isEmpty())
  {
    queueFront = 0;
    queueEnd = 0;
    queue[queueEnd] = player;
  }
  else if (isFull())
  {
    cout << "Queue full, cannot add new item" << endl;
  }
  else
  {
    queueEnd = (queueEnd + 1)%SIZE;
    queue[queueEnd] = player;
  }
}

void ProducerConsumer :: dequeue()
{
  if (isEmpty())
  {
    cout << "Queue empty, cannot dequeue an item" << endl;
  }
  else if (queueFront == queueEnd)
  {
    queueFront = -1;
    queueEnd = -1;
  }
  else
  {
    queueFront = (queueFront + 1)%SIZE;
  }
}
int ProducerConsumer :: queueSize()
{
  int size;
  if (queueEnd == -1)
  {
      return 0;
  }
  size = (queueEnd + SIZE - queueFront)%SIZE + 1;
  return size;
}

string ProducerConsumer :: peek()
{
  if (isEmpty())
  {
    cout << "Queue empty, cannot peek" << endl;
    return "";
  }
  return queue[queueFront];
}
