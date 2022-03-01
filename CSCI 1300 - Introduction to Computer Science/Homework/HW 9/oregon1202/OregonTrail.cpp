#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>
// #include "Date.h"
// #include "Bullets.h"
// #include "Food.h"
// #include "MiscSupplies.h"
//#include "Oxen.h"
//#include "Player.h"
// #include "Distance.h"
#include "OregonTrail.h"

using namespace std;

OregonTrail::OregonTrail()
{
    numPlayers = 0;
    currentPlayer = 0;
}

int OregonTrail::addPlayer(int pID, string pName)
{
    players[pID].setPlayerID(pID);
    players[pID].setPlayerName(pName);

    numPlayers++;
    
    return numPlayers;
}

string OregonTrail::getPlayerName(int pID)
{
    return players[pID].getPlayerName();
}

void OregonTrail::setCurrentPlayer(int pID)
{
    currentPlayer = pID;
}

void OregonTrail::sickness(int pID)
{
    numPlayers = numPlayers - 1;
    players[pID].iamSick();
}

void OregonTrail::setMainPlayer(int pID)
{
    players[pID].setMainPlayer();
}

int OregonTrail::currMileOnTrip(int pID)
{
    return players[pID].getCurrMile();
}

int OregonTrail::poundsFood(int pID)
{
    return players[pID].getPoundsFood();
}

int OregonTrail::numBullets(int pID)
{
    return players[pID].getNumBullets();
}

int OregonTrail::totalCash(int pID)
{
    return players[pID].getTotalMoney();
}

void OregonTrail::addVisitStoreCnt(int pID)
{
    players[pID].addVisitStore();
}

int OregonTrail::getVisitStoreCnt(int pID)
{
    return players[pID].getVisitStore();
}

void OregonTrail::visitStore(int playerID)
{
    int category;
    int numOfYokes;
    int pounds;
    int boxes;
    int parts;
    int kits;
    string yesORno = "y";
    
    cout << "Welcome to the Store!" << endl;
    cout << "YOU HAD SAVED $1200 TO SPEND FOR THE TRIP, AND YOU'VE INITIALLY PAID $200 FOR A WAGON. YOU WILL NEED TO SPEND THE REST OF YOUR MONEY ON THE FOLLOWING ITEMS:" << endl;
    cout << "- OXEN. YOU CAN SPEND $100-$200 ON YOUR TEAM. THE MORE YOU SPEND, THE FASTER YOU'LL GO BECAUSE YOU'LL HAVE BETTER ANIMALS" << endl;
    cout << "- FOOD. THE MORE YOU HAVE, THE LESS CHANCE THERE IS OF GETTING SICK" << endl;
    cout << "- BULLETS - $2 BUYS A BELT OF 20 BULLETS. YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS AND BANDITS, AND FOR HUNTING FOOD" << endl;
    cout << "- MISCELLANEOUS SUPPLIES. THIS INCLUDES MEDICINE AND OTHER THINGS YOU WILL NEED FOR SICKNESS AND EMERGENCY REPAIRS" << endl;
    cout << "YOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP, OR YOU CAN SAVE SOME OF YOUR CASH TO SPEND AT FORTS ALONG THE WAY WHEN YOU RUN LOW. HOWEVER, ITEMS COST MORE AT THE FORTS. YOU CAN ALSO GO HUNTING ALONG THE WAY TO GET MORE FOOD." << endl;
    cout << "Right now you have: $" << players[playerID].getTotalMoney() << ".00" << endl << endl;
    
    players[playerID].setWagon();
    cout << "Now, you got a wagon, and then paid $200.00 for it." << endl;
again:
    cout << "What would you like to purchase? (1. Oxen  2. Food  3. Bullets  4. Miscellaneous) Your pick  5. Leave the store?: ";
    cin >> category;
    switch(category)
    {
        case 1:
            cout << "1. Oxen: You must spend between $100 to $200 dollars on oxen. There are 2 oxen in a yoke and the price of each yoke is $40.0. How many yokes do you wish to purchase?: ";
            cin >> numOfYokes;
            
            if ( (players[playerID].getPriceOxen() + (numOfYokes * 2 * 20.0) ) > 200.00 )
            {
                cout << "You must spend between $100 and $200 dollars on oxen! Your Purchase has been cancelled." << endl;
                goto again;
            }
            else
            {
                players[playerID].setNumOxen(numOfYokes);
                cout << "The current bill so far: $" << players[playerID].getCurrentBill() << endl;
            }
            break;
        case 2:
            cout << "2. Food: The store owner recommends you should purchase at least 200 lbs of food per person, at 50 cents per pound. How many pounds of food do you wish to purchase?: ";
            cin >> pounds;
            players[playerID].setPounds(pounds);
            cout.precision(2);
            cout << fixed;
            cout << "The current bill so far: $" << players[playerID].getCurrentBill() << endl;
            break;
        case 3:
            cout << "3. Bullets: A box of bullets costs $2. How many boxes of bullets do you wish to purchase?: ";
            cin >> boxes;
            players[playerID].setBullets(boxes);
            cout.precision(2);
            cout << fixed;
            cout << "The current bill so far: $" << players[playerID].getCurrentBill() << endl;
            break;
        case 4:
            cout << "4. Miscellaneous Supplies:" << endl;
            cout << " - A wagon parts (wheels, axles, tongues) costs $20. How many parts do you wish to purchase?: ";
            cin >> parts;
            players[playerID].setParts(parts);
            cout << " - A medical aid kit costs $25. How many kits do you wish to purchase?: ";
            cin >> kits;
            players[playerID].setKits(kits);
            cout.precision(2);
            cout << fixed;
            cout << "The current bill so far: $" << players[playerID].getCurrentBill() << endl;
            break;
        case 5:
            cout << "Bye bye! CU again!" << endl;
            break;
        default:
            cout << "You have to pick one of 1 ~ 5!" << endl;
            goto again;
    }
    
    if (category != 5)
    {
        if ( players[playerID].getCurrentBill() <= players[playerID].getTotalMoney() )
        {
            cout << "Do you want to pay now? (y / n) ";
            cin >> yesORno;
            if ( yesORno == "y" )
            {
                players[playerID].payMoney();
                cout << "The current totoal money: $" << players[playerID].getTotalMoney() << endl;
                players[playerID].printBill();
                players[playerID].resetCategoryBill();
            }
        }
        else
        {
            cout << "The current total money is not enoug to purchase these things that you picked up!" << endl;
            cout << "Returned them now, and purchase other categories, again." << endl;
            players[playerID].returnCategory();

        }
        goto again;
    }
    else if ( players[playerID].getPriceOxen() < 100.0 )
    {
        cout << "You must spend between $100 and $200 dollars on oxen! Your Purchase has to be continued." << endl;
        goto again;
    }
}


//void statusUpdate();
//int hunt() {return food;};
//void misfortunes();
//void raiderAttack();
//bool puzzles();


