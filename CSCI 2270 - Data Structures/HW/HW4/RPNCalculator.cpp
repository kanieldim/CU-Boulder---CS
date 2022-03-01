#include "RPNCalculator.hpp"

using namespace std;


RPNCalculator :: RPNCalculator()
{
  stackHead = nullptr;
}

RPNCalculator :: ~RPNCalculator()
{
  while (stackHead != nullptr)
  {
    pop();
  }
  stackHead = nullptr;
}

bool RPNCalculator :: isEmpty()
{
  if(stackHead == nullptr)
  {
    return true;
  }
return false;
}

void RPNCalculator :: push (float number)
{
  Operand *temp = new Operand;
  temp -> number = number;
  temp -> next = nullptr;

  if (isEmpty())
  {
    stackHead = temp;
  }
  else
  {
    temp -> next = stackHead;
    stackHead = temp;
  }
}

void RPNCalculator :: pop()
{
  if (!isEmpty())
  {
    Operand *temp = stackHead;
    stackHead = stackHead -> next;
    delete temp;
  }
  else
  {
    cout << "Stack empty, cannot pop an item." << endl;
  }
}

Operand* RPNCalculator :: peek()
{
  if (stackHead == nullptr)
  {
    cout << "Stack empty, cannot peek." << endl;
    return nullptr;
  }
  else
  {
    Operand *temp = stackHead;
    return temp;
  }
}

bool RPNCalculator :: compute(string symbol)
{
  float firstTop, secondTop, result;
  if (symbol != "+" && symbol != "*")
  {
    cout << "err: invalid operation" << endl;
    return false;
  }
  else if (symbol == "+" || symbol == "*")
  {
    if (stackHead == nullptr)
    {
      cout << "err: not enough operands" << endl;
      return false;
    }
    else
    {
      if (stackHead == nullptr || stackHead -> next == nullptr)
      {
        cout << "err: not enough operands" << endl;
        return false;
      }
      Operand *temp = stackHead -> next;
      firstTop = stackHead -> number;
      secondTop = temp -> number;
      if (symbol == "+")
      {
        result = firstTop + secondTop;
        pop();
        pop();
        push(result);
        return true;
      }
      else if (symbol == "*")
      {
        result = firstTop * secondTop;
        pop();
        pop();
        push(result);
        return true;
      }
    }
  }
}
