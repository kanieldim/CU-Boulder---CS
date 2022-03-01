#include "Oxen.h"

using namespace std;

Oxen::Oxen()
{
    numWagon = 0;
    numOxen = 0;
    numYokes = 0;
    
    numCategory = 0;
    numCategoryOxen = 0;
    categoryBill = 0.0;
    currentBill = 0;
}

void Oxen::setNumWagon(int numOfWagon)
{
    numWagon = numOfWagon;
}

void Oxen::addNumWagon(int numOfWagon)
{
    numWagon = numWagon + numOfWagon;
}

void Oxen::brokenWagon()
{
    numWagon = numWagon - 1;
}

void Oxen::setNumYokes(int numOfYokes)
{
    numYokes = numOfYokes;
}

void Oxen::addNumYokes(int numOfYokes)
{
    numYokes = numYokes + numOfYokes;
}

void Oxen::brokenYokes()
{
    numYokes = numYokes - 1;
}

void Oxen::setNumOxen(int numOfYokes)
{
    numYokes += numOfYokes;
    numCategory = numOfYokes;
    numOxen = (2 * numYokes);
    numCategoryOxen = numOfYokes * 2;
    priceOxen = (numOxen * 20.0);
    categoryBill = numCategoryOxen * 20.0;
    currentBill += categoryBill;
    //totalCash = totalCash - currentBill;
}

void Oxen::addNumOxen(int numOfOxen)
{
    numOxen = numOxen + numOfOxen;
}

void Oxen::deadOxen()
{
    numOxen = numOxen - 1;
}

void Oxen::resetCategoryBill()
{
    categoryBill = 0.0;
    numCategory = 0;
    numCategoryOxen = 0;
}

void Oxen::printOxenBill()
{
    cout << " - " << "Wagon " << "\t " << "1" << " ea\t" << " $" << "200.00" << endl;
    cout << " - " << "Oxen " << "\t " << numOxen << " ea\t" << " $" << priceOxen << endl;
    cout << "   " << "Yokes " << "\t " << numYokes << " ea\t" << endl;
}
