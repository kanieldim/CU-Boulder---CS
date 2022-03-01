#include <iostream>
#include "Player.h"

#ifndef OREGONTRAIL_H
#define OREGONTRAIL_H

class OregonTrail
{
    Player players[5];
    
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
    
    void visitStore(int);
    int getNumPlayers(void) { return numPlayers; };
    void setCurrentPlayer(int);
    int getCurrentPlayer(void) { return currentPlayer; };
    void setMainPlayer(int);
    int currMileOnTrip(int);
    int poundsFood(int);
    int numBullets(int);
    int totalCash(int);
    //void statusUpdate();
    //int hunt();
    //void misfortunes();
    //void raiderAttack();
    //bool puzzles();
    
};

#endif
