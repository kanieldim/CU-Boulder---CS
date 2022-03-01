#include <iostream>
//#include "Food.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    int playerID;
    string playerName;
    int numPlayers;
    
    int numVisitStore;
    int numOxen;
    float priceOxen;
    int numYokes;
    int wagon;
    int poundsFood;
    float priceFood;
    int boxesBullets;
    int numBullets;
    float priceBullets;
    int numParts;
    float priceParts;
    int numKits;
    float priceKits;
    float totalCash;
    float currentBill;
    float categoryBill;
    int numCategory;
    int numCategoryOxen;
    int numCategoryParts;
    int numCategoryKits;

    int mainPlayer = 0;
    int sick = 0;
    int turnsTaken = 0;
    int currMile = 0;
    
    
    public:
    
    Player();
    
    void setPlayerID(int);
    void setPlayerName(string);
    string getPlayerName() { return playerName; };
    
    int getVisitStore(void);
    void addVisitStore(void);
    void setWagon(void) { wagon = 1; totalCash -= 200; };
    void setNumOxen(int);
    float getPriceOxen() { return priceOxen; };
    void setPounds(int);
    void setBullets(int);
    void setParts(int);
    void setKits(int);
    void resetCategoryBill();
    void returnCategory() { currentBill -= categoryBill; };
    float getTotalMoney() { return totalCash; };
    float getCurrentBill() { return currentBill; }
    void printBill();
    void currentCost(int);
    void payMoney();
    
    void iamSick() { sick = 1; };
    void setMainPlayer() { mainPlayer = 1; };
    void addTurnsTaken() { turnsTaken++; };
    int getTurnsTaken() { return turnsTaken; };
    void setCurrMile(int);
    int getCurrMile() { return currMile; };
    int getPoundsFood() { return poundsFood; };
    int getNumBullets() { return numBullets; };

    
};

#endif
