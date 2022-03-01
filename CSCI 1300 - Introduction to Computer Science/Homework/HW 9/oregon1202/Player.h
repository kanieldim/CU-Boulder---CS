#include <iostream>
//#include "Food.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    int playerID;
    string playerName;
    
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
    string getPlayerName(void) { return playerName; };
    
    int getVisitStore(void);
    void addVisitStore(void);
    void setWagon(void) { wagon = 1; totalCash -= 200; };
    void setNumOxen(int);
    float getPriceOxen() { return priceOxen; };
    void setPounds(int);
    void setBullets(int);
    void setParts(int);
    void setKits(int);
    void resetCategoryBill(void);
    void returnCategory(void) { currentBill -= categoryBill; };
    float getTotalMoney(void) { return totalCash; };
    float getCurrentBill(void) { return currentBill; }
    void printBill(void);
    void currentCost(int);
    void payMoney(void);
    
    void iamSick(void) { sick = 1; };
    void setMainPlayer(void) { mainPlayer = 1; };
    void addTurnsTaken(void) { turnsTaken++; };
    int getTurnsTaken(void) { return turnsTaken; };
    void setCurrMile(int);
    int getCurrMile(void) { return currMile; };
    int getPoundsFood(void) { return poundsFood; };
    int getNumBullets(void) { return numBullets; };

    
};

#endif
