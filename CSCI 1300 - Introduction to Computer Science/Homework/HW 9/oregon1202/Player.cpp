#include <string>
#include "Player.h"

using namespace std;

Player::Player()
{
    numVisitStore = 0;
    numOxen = 0;
    numYokes = 0;
    wagon = 0;
    numParts = 0;
    numKits = 0;
    boxesBullets = 0;
    numBullets = 0;
    poundsFood = 0;
    currentBill = 0.0;
    categoryBill = 0.0;
    numCategory = 0;
    numCategoryOxen = 0;
    numCategoryParts = 0;
    numCategoryKits = 0;
    totalCash = 1200.0;
    mainPlayer = 0;
    sick = 0;
    currMile = 0;
}

void Player::setPlayerID(int playerIDAssigned)
{
    playerID = playerIDAssigned;
}

void Player::setPlayerName(string nameAssigned)
{
    playerName = nameAssigned;
}

void Player::addVisitStore(void)
{
    numVisitStore++;
}

int Player::getVisitStore(void)
{
    return numVisitStore;
}

void Player::setNumOxen(int numOfYokes)
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

void Player::setPounds(int pounds)
{
    poundsFood += pounds;
    numCategory = pounds;
    priceFood += (0.5 * pounds);
    categoryBill = pounds * 0.5;
    currentBill += categoryBill;
    //totalCash = totalCash - currentBill;
}

void Player::setBullets(int boxes)
{
    boxesBullets += boxes;
    numCategory = boxes;
    priceBullets += (boxes * 2.0);
    categoryBill = boxes * 2.0;
    currentBill += categoryBill;
    numBullets = boxesBullets * 20;
    //totalCash -= currentBill;
}

void Player::setParts(int parts)
{
    numParts += parts;
    numCategoryParts = parts;
    priceParts += (parts * 20.0);
    categoryBill = parts * 20.0;
    //currentBill += categoryBill;
    //totalCash -= currentBill;
}

void Player::setKits(int kits)
{
    numKits += kits;
    numCategoryKits = kits;
    priceKits += (kits * 25.0);
    categoryBill += kits * 25.0;
    currentBill += categoryBill;
    //totalCash -= currentBill;
}

void Player::resetCategoryBill()
{
    categoryBill = 0.0;
    numCategory = 0;
    numCategoryOxen = 0;
    numCategoryParts = 0;
    numCategoryKits = 0;
}

void Player::printBill(void)
{
    cout << "The bill purchased so far for the customer, " << playerName << endl;
    cout << " - " << "Wagon " << "\t " << "1" << " ea\t" << " $" << "200.00" << endl;
    cout << " - " << "Oxen " << "\t " << numOxen << " ea\t" << " $" << priceOxen << endl;
    cout << "   " << "Yokes " << "\t " << numYokes << " ea\t" << endl;
    cout << " - " << "Food " << "\t " << poundsFood << "lbs\t" << " $" << priceFood << endl;
    cout << " - " << "Bullets " << "\t " << boxesBullets << " bxs\t" << " $" << priceBullets << endl;
    cout << " - " << "Parts " << "\t " << numParts << " ea\t" << " $" << priceParts << endl;
    cout << " - " << "M. Kits " << "\t " << numKits << " ea\t" << " $" << priceKits << endl;
    cout << "   " << "Current Total " << "\t $" << (1200 - totalCash) << endl;
}

void Player::currentCost(int currentMoney)
{
    currentBill = currentBill + currentMoney;
}

void Player::payMoney()
{
    totalCash = totalCash - currentBill;
    currentBill = 0.0;
}

void Player::setCurrMile(int cMile)
{
    currMile = cMile;
}
