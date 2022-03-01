#include <iostream>
#include "Player.h"
#include "Oxen.h"
#include "Food.h"
#include "Bullets.h"
#include "MiscSupplies.h"

#ifndef OREGONTRAIL_H
#define OREGONTRAIL_H

class OregonTrail
{
    Player players[5];
    Oxen oxen;
    Food food;
    Bullets bullets;
    MiscSupplies miscSupplies;
    
    int numPlayers;
    int currentPlayer;
    int mainPlayer;
    
    
    public:
    
    OregonTrail();
    
    int addPlayer(int, string);
    string getPlayerName(int);
    void sickness(int);
    void addVisitStoreCnt(int);
    int getVisitStoreCnt(int);
    
    void visitStoreFirst();
    
    int getNumPlayers() { return numPlayers; };
    void setCurrentPlayer(int);
    int getCurrentPlayer() { return currentPlayer; };
    void setMainPlayer(int);
    int currMileOnTrip(int);
    float totalCash();
    void setNumOxen(int);
    int poundsFood();
    void spendFood(int);
    int numBullets();
    int numParts();
    int numKits();
    
    
    bool doPuzzles();
    void goHunting();
    void afterHunting();

    //void statusUpdate();
    //void misfortunes();
    //void raiderAttack();
};

#endif
