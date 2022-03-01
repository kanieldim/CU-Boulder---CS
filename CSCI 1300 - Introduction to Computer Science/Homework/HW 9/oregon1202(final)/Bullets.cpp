#include <string>
#include "Bullets.h"

using namespace std;

Bullets::Bullets()
{
    totalBoxes = 0;
    totalBullets = 0;
    
    boxesBullets = 0;
    numCategory = 0;
    priceBullets = 0.0;
    categoryBill = 0.0;
    currentBill = 0.0;
    numBullets = 0;
}

void Bullets::addBoxesCount(int addBoxes)
{
    totalBoxes = totalBoxes + addBoxes;
}

void Bullets::addBulletsCount(int addBullets)
{
    totalBullets = totalBullets + addBullets;
}

void Bullets::subBulletsCount(int subBullets)
{
    totalBullets = totalBullets - subBullets;
}

void Bullets::huntRabbit()
{
    totalBullets = totalBullets - 10;
}

void Bullets::huntFox()
{
    totalBullets = totalBullets - 8;
}

void Bullets::huntDeer()
{
    totalBullets = totalBullets - 5;
}

void Bullets::huntBear()
{
    totalBullets = totalBullets - 10;
}

void Bullets::huntMoose()
{
    totalBullets = totalBullets - 12;
}

void Bullets::setBullets(int boxes)
{
    boxesBullets += boxes;
    numCategory = boxes;
    priceBullets += (boxes * 2.0);
    categoryBill = boxes * 2.0;
    currentBill += categoryBill;
    numBullets = boxesBullets * 20;
    //totalCash -= currentBill;
    totalBullets += numBullets;
}
void Bullets::printBulletsBill()
{
    cout << " - " << "Bullets " << "\t " << numBullets << "ea\t" << " $" << priceBullets << endl;
}
void Bullets::resetCategoryBill()
{
    categoryBill = 0.0;
    numCategory = 0;
}
