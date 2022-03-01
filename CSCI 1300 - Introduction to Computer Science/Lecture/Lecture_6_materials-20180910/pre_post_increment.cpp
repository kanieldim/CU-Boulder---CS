#include <iostream>
using namespace std;

int main()
{
    int intA, intB;
    intA = 2;
    intB = 2 * intA++;
    cout << "intA = " << intA << " and intB = " << intB << endl;

    intA = 2;
    intB = 2 * ++intA;
    cout << "intA = " << intA << " and intB = " << intB << endl;


    return 0;
}
