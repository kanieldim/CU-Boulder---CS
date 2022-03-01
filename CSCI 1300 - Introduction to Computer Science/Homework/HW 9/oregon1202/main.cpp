#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// #include "Date.h"
// #include "Bullets.h"
// #include "Food.h"
// #include "MiscSupplies.h"
//#include "Oxen.h"
// #include "Player.h"
// #include "Distance.h"
#include "OregonTrail.h"

using namespace std;

OregonTrail OTtrip;

int StartingMenu()
{
    int playerID = 0;
    string playerName;
    
    cout << "THE OREGON TRAIL GAME" << endl << endl;

    cout << "What is your name?: ";
    cin >> playerName;
    OTtrip.setMainPlayer(playerID);
    playerID = OTtrip.addPlayer(playerID, playerName);
    cout << "The leader of the trip: " << OTtrip.getPlayerName(0) << endl;
    cout << "Please enter the names of your companions below: " << endl;
    while (playerID < 5 )
    {
        cout << playerID << ". ";
        cin >> playerName;
        playerID = OTtrip.addPlayer(playerID, playerName);
    }
    
    return OTtrip.getNumPlayers();
}

int TakingTurns(void)
{
    int numPlayers;
    int currentPlayer;
    
    numPlayers = OTtrip.getNumPlayers();
    cout << "The following are the travellers: " << endl;
    for ( int i = 0; i < numPlayers; i++ )
        cout << i << ". " << OTtrip.getPlayerName(i) << endl;
    cout << "Who's the next player?" << " This turn gives to ";
    currentPlayer = rand() % numPlayers;
    cout << OTtrip.getPlayerName(currentPlayer) << endl;
    cout << "Now, " << OTtrip.getPlayerName(currentPlayer) << "'s ";
    cout << "turn to kick the road over the Oregon Trail from Indpendence, Missouri to Oregon City, Oregon!" << endl << endl;
   
    cout << " - The current date: " << endl;
    cout << " - You are starting at mile: " << OTtrip.currMileOnTrip(currentPlayer) << endl;
    cout << " - There are "<< (2040 - OTtrip.currMileOnTrip(currentPlayer)) << " miles that you must travel to reach your destination." << endl;
    cout << " - Food available now is " << OTtrip.poundsFood(currentPlayer) << " lbs" <<endl;
    cout << " - Number of bullets available now is " << OTtrip.numBullets(currentPlayer) << endl;
    cout << " - Cash available now is $" << OTtrip.totalCash(currentPlayer) << endl;

    return currentPlayer;
}

int main()
{
    // Player Pla;
    // Bullets Bul;
    // Food Foo;
    // MiscSupplies Mis;
    // Oxen Oxe;
    // Distance Dis;
    
    int numPlayers;
    int currentPlayer;
    int storeVisitCnt[5] = {0};
    string yesOrNo;
    
    numPlayers = StartingMenu();
    
    currentPlayer = TakingTurns();

    cout << endl << OTtrip.getPlayerName(currentPlayer) << ", Start a trip:" << endl;
    cout << "Before the start of your trip, you can visit the store and buy supplies: food, oxen, bullets and wagon parts." << endl;
    cout << "Would you like to visit the store? (Y / N) ";
    cin >> yesOrNo;
    
    if (yesOrNo == "yes" || yesOrNo == "Yes" || yesOrNo == "y" || yesOrNo == "Y")
    {
        OTtrip.visitStore(currentPlayer);
        storeVisitCnt[currentPlayer] = storeVisitCnt[currentPlayer] + 1;
        cout << "Your visit count to the store: " << storeVisitCnt[currentPlayer] << " time(s)" << endl;
    }
    
}
