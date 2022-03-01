#include <string>
#include "Player.h"

using namespace std;

Player::Player()
{
    numVisitStore = 0;
    //numOxen = 0;
    //numYokes = 0;
    //wagon = 0;
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

void Player::resetCategoryBill()
{
    categoryBill = 0.0;
    numCategory = 0;
    numCategoryOxen = 0;
    numCategoryParts = 0;
    numCategoryKits = 0;
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
