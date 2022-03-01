#include <iostream>

using namespace std;

class StackLL
{
  private:
    const int SIZE = 5;
    int *stack;
    int top;
    int capacity;
    void doubleArr();
    void halveArr();

  public:
    StackLL();
    ~StackLL();
    void push(int value);
    void pop();
    void print();
    int getCapacity() {return capacity;}
};

void StackLL :: doubleArr()
{
  int *newArray = new int[capacity*2];
  for (int i = 0; i < top+1; i++)
  {
    newArray[i] = stack[i];
  }
  delete [] stack;
  stack = newArray;
  capacity *= 2;
}

void StackLL :: halveArr()
{
  int *newArray = new int[capacity/2];
  for (int i = 0; i < top+1; i++)
  {
    newArray[i] = stack[i];
  }
  delete [] stack;
  stack = newArray;
  capacity /= 2;
}

StackLL::StackLL()
{
  stack = new int[SIZE];
  top = -1;
  capacity = SIZE;
}

StackLL::~StackLL()
{
  delete [] stack;
}

void StackLL :: push(int value)
{
  if (top == capacity - 1)
  {
    doubleArr();
  }
  top++;
  stack[top] = value;
}

void StackLL :: pop()
{
  top--;
  if (top <= capacity/2 && capacity >= 10)
  {
    halveArr();
  }
}

void StackLL :: print()
{
  for (int i = 0; i < top; i++)
  {
    cout << stack[i] << " : ";
  }
  cout << stack[top] << endl;
}

int main(int argc, char const *argv[])
{
	StackLL s;
	s.push(1);
	s.push(1);
	s.push(1);
	s.push(1);
	s.push(1);
	s.push(1);
	s.push(1);
	s.push(1);
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.print();
	cout << s.getCapacity() << endl;
	return 0;
}
