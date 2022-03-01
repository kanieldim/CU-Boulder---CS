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

void TakingTurns()
{
    int numPlayers;
    int currentPlayer;
    int choice;
    int restDays;
    int pounds;
    int trailDays;
    int huntingDays;
    
    numPlayers = OTtrip.getNumPlayers();
    cout << "The following are the travellers: " << endl;
    for ( int i = 0; i < numPlayers; i++ )
        cout << i << ". " << OTtrip.getPlayerName(i) << endl;
    cout << "Who's the next player?" << " This turn gives to ";
    currentPlayer = rand() % numPlayers;
    cout << OTtrip.getPlayerName(currentPlayer) << endl;
    cout << "Now, " << OTtrip.getPlayerName(currentPlayer) << "'s ";
    cout << "turn to kick the road over the Oregon Trail from Indpendence, Missouri to Oregon City, Oregon!" << endl << endl;
  
    while (1)
    {
        cout << " - The current date: " << endl;
        cout << " - You are starting at mile: " << OTtrip.currMileOnTrip(currentPlayer) << " miles" <<endl;
        cout << " - There are "<< (2040 - OTtrip.currMileOnTrip(currentPlayer)) << " miles that you must travel to reach your destination." << endl;
        cout << " - Food available now is " << OTtrip.poundsFood() << " lbs" <<endl;
        cout << " - Number of bullets available now is " << OTtrip.numBullets() << " bullets" << endl;
        cout.precision(2);
        cout << fixed;
        cout << " - Cash available now is $" << OTtrip.totalCash() << endl << endl;
        
        cout << "What is the action in your turn? " << endl;
        cout << "1. Stop to rest  2. Continue on the trail  3. Go Hunting  4. Quit (Your choice: 1 ~ 4 ) ";
        cin >> choice;
        
        if (choice == 1)
        {
            cout << endl << "How many days you want to rest (1 day ~ 3 days)? ";
            cin >> restDays;
            pounds = 3 * restDays * numPlayers;
            OTtrip.spendFood(pounds);
            //travel days update here
        }
        else if (choice == 2)
        {
            trailDays = 14;
            pounds = 3 * trailDays * numPlayers;
            OTtrip.spendFood(pounds);
            // travel distance update here between 70 miles and 140 miles per turn
        }
        else if (choice == 3)
        {
            cout << "How many days do you want to go hunting? (1 day ~ 14 days) ";
            cin >> huntingDays;
            for (int i=0; i < huntingDays; i++)
            {
                OTtrip.goHunting();
            }
            OTtrip.afterHunting();
        }
        else if (choice == 4)
        {
            cout << "The game ends. The travelling party had to cut this trip short." << endl;
            return;
        }
    }
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
    int currentPlayer = 0;
    int storeVisitCnt[5] = {0};
    string yesOrNo;
    
    numPlayers = StartingMenu();
    
    cout << endl << OTtrip.getPlayerName(currentPlayer) << ", Start a trip:" << endl;
    cout << "Before the start of your trip, you can visit the store and buy supplies: food, oxen, bullets and wagon parts." << endl;
    cout << "Would you like to visit the store? (Y / N) ";
    cin >> yesOrNo;
    
    if (yesOrNo == "yes" || yesOrNo == "Yes" || yesOrNo == "y" || yesOrNo == "Y")
    {
        OTtrip.visitStoreFirst();
        storeVisitCnt[currentPlayer] = storeVisitCnt[currentPlayer] + 1;
        cout << "Your visit count to the store: " << storeVisitCnt[currentPlayer] << " time(s)" << endl;
    }
    
    TakingTurns();

}
