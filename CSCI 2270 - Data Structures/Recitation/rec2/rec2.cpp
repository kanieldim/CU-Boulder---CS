#include <iostream>

using namespace std;

// & "reference variable"
// address of operator / returns address of variable  &<variable>

// *
// pointer variable <type> * <name>
// dereference get value troed at address *<pointer variable>


void func(int *x)
{
  *x = 12*(*x)+7;
  //cout << x << endl;
}

int main()
{
  int x = 4;
  // cout << x << endl;
  // cout << &x << endl;
  func(&x);
  cout << x << endl;
  return 0;

}
//
// struct Distance
// {
//   int feet;
//   int inch;
// };
//
// int main()
// {
//   Distance d;
//   Distance* ptr;
//   d.feet = 8;
//   d.inch = 6;
//
//   ptr = &d;
//   cout << "Distance = " << ptr->feet << "ft" << ptr->inch << "inches";
// }
