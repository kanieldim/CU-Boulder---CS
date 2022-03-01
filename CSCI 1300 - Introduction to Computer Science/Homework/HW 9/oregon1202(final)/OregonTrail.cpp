#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>
// #include "Date.h"
#include "Bullets.h"
#include "Food.h"
// #include "MiscSupplies.h"
#include "Oxen.h"
//#include "Player.h"
// #include "Distance.h"
#include "OregonTrail.h"

using namespace std;

OregonTrail::OregonTrail()
{
    numPlayers = 0;
    currentPlayer = 0;
}

void OregonTrail::setNumOxen(int ox)
{
    oxen.setNumOxen(ox);
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

int OregonTrail::poundsFood()
{
    return food.getTotalFood();
}

void OregonTrail::spendFood(int pounds)
{
    food.eatenFood(pounds);
}

int OregonTrail::numBullets()
{
    return bullets.getBulletsCount();
}

int OregonTrail::numParts()
{
    return miscSupplies.getNumParts();
}
int OregonTrail::numKits()
{
    return miscSupplies.getNumKits();
}

float OregonTrail::totalCash()
{
    float cash = 0.0;
    cash += oxen.getPriceOxen();
    cash += food.getPriceFood();
    cash += bullets.getPriceBullets();
    cash += miscSupplies.getPriceParts();
    cash += miscSupplies.getPriceKits();

    return 1000.0 - cash;
}

void OregonTrail::addVisitStoreCnt(int pID)
{
    players[pID].addVisitStore();
}

int OregonTrail::getVisitStoreCnt(int pID)
{
    return players[pID].getVisitStore();
}

void OregonTrail::visitStoreFirst()
{
    int playerID = 0;
    int category;
    int numOfYokes;
    int pounds;
    int boxes;
    int parts;
    int kits;
    string yesORno = "y";
    float currentCash;
    
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
            
            if ( (oxen.getPriceOxen() + (numOfYokes * 2 * 20.0) ) > 200.00 )
            {
                cout << "You must spend between $100 and $200 dollars on oxen! Your Purchase has been cancelled." << endl;
                goto again;
            }
            else
            {
                oxen.setNumOxen(numOfYokes);
                cout << "The current bill so far: $" << oxen.getCurrentBill() << endl;
            }
            break;
        case 2:
            cout << "2. Food: The store owner recommends you should purchase at least 200 lbs of food per person, at 50 cents per pound. How many pounds of food do you wish to purchase?: ";
            cin >> pounds;
            food.setTotalFood(pounds);
            cout.precision(2);
            cout << fixed;
            cout << "The current bill so far: $" << food.getCurrentBill() << endl;
            break;
        case 3:
            cout << "3. Bullets: A box of bullets costs $2. How many boxes of bullets do you wish to purchase?: ";
            cin >> boxes;
            bullets.setBullets(boxes);
            cout.precision(2);
            cout << fixed;
            cout << "The current bill so far: $" << bullets.getCurrentBill() << endl;
            break;
        case 4:
            cout << "4. Miscellaneous Supplies:" << endl;
            cout << " - A wagon parts (wheels, axles, tongues) costs $20. How many parts do you wish to purchase?: ";
            cin >> parts;
            miscSupplies.setNumParts(parts);
            cout << " - A medical aid kit costs $25. How many kits do you wish to purchase?: ";
            cin >> kits;
            miscSupplies.setNumKits(kits);
            cout.precision(2);
            cout << fixed;
            cout << "The current bill so far: $" << miscSupplies.getCurrentBill() << endl;
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
                cout << "The current totoal money: $" << totalCash() << endl;
                cout << "The bill purchased so far for the customer, " << players[playerID].getPlayerName() << endl;
                oxen.printOxenBill();
                currentCash = 200 + oxen.getCurrentBill();
                food.printFoodBill();
                currentCash = currentCash + food.getCurrentBill();
                bullets.printBulletsBill();
                currentCash = currentCash + bullets.getCurrentBill();
                miscSupplies.printMiscBill();
                currentCash = currentCash + miscSupplies.getCurrentBill();
                cout << "   " << "Current Total " << "\t $" << currentCash << endl;
                oxen.resetCategoryBill();
                food.resetCategoryBill();
                bullets.resetCategoryBill();
                miscSupplies.resetCategoryBill();
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
    else if ( oxen.getPriceOxen() < 100.0 )
    {
        cout << "You must spend between $100 and $200 dollars on oxen! Your Purchase has to be continued." << endl;
        goto again;
    }
}

bool OregonTrail::doPuzzles()
{
    bool result = false;
    int guessANumber;
    int randomNumber;
    
    cout << "Welcome to the puzzle!" << endl;
    cout << "In order to pass this puzzle, you must correctly guess a number between 1 to 10." << endl;
    cout << "You will be given at most 3 tries. Good luck!" << endl;
    randomNumber = rand()%10 + 1;
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << " try! Your guess?: ";
        cin >> guessANumber;
        cout << endl;
        if (guessANumber == randomNumber)
        {
            cout << "You have passed the puzzle!" << endl;
            //cout << "Used " << bullet << "bullets!" << endl;
            //cout << "Food improved by: " << food << endl;
            result = true;
            break;
        }
    }
    if (result == false)
    {
        cout << "You have FAILED the puzzle!" << endl;
        cout << "Failed the puzzle! Hunt opportunity missed. moving on!" << endl;
    }
    
    return result;
}

void OregonTrail::goHunting()
{
    int probability;
    string yesORno;
    bool puzzlesResult;
    int eatQuality;
    int pounds;
    
    probability = rand()%100 + 1;
    if (probability >= 1 && probability <= 50)
    {
        cout << "You got lucky! You encountered a rabbit! Do you want to hunt: (1) Yes, (2) No " ;
        cin >> yesORno;
        
        if (yesORno == "yes" || yesORno == "Yes" || yesORno == "y" || yesORno == "Y" || yesORno == "1")
        {
            if (bullets.getBulletsCount() > 10)
            {
                bullets.subBulletsCount(10);
                puzzlesResult = doPuzzles();
                if (puzzlesResult == true)
                {
                    food.rabbitFood();
                }
            }
            else
                cout << "You have no enough bullets! You can't hunt it." << endl;
        }
        else
        {
            cout << "No huntings for today I guess!" << endl;
        }
    }
    else if (probability > 50 && probability <= 75)
    {
        cout << "You got lucky! You encountered a fox! Do you want to hunt: (1) Yes, (2) No " ;
        cin >> yesORno;
        if (yesORno == "yes" || yesORno == "Yes" || yesORno == "y" || yesORno == "Y" || yesORno == "1")
        {
            if (bullets.getBulletsCount() > 10)
            {
                bullets.subBulletsCount(8);
                puzzlesResult = doPuzzles();
                if(puzzlesResult == true)
                {
                    food.foxFood();
                }
            }
            else
                cout << "You have no enough bullets! You can't hunt it." << endl;
        }
        else
        {
            cout << "No huntings for today I guess!" << endl;
        }
    }
    else if (probability > 75 && probability <= 90)
    {
        cout << "You got lucky! You encountered a deer! Do you want to hunt: (1) Yes, (2) No " ;
        cin >> yesORno;
        if (yesORno == "yes" || yesORno == "Yes" || yesORno == "y" || yesORno == "Y" || yesORno == "1")
        {
            if (bullets.getBulletsCount() > 10)
            {
                bullets.subBulletsCount(5);
                puzzlesResult = doPuzzles();
                if(puzzlesResult == true)
                {
                    food.deerFood();
                }
            }
            else
                cout << "You have no enough bullets! You can't hunt it." << endl;
        }
        else
        {
            cout << "No huntings for today I guess!" << endl;
        }
    }
    else if (probability > 90 && probability <= 97)
    {
        cout << "You got lucky! You encountered a bear! Do you want to hunt: (1) Yes, (2) No " ;
        cin >> yesORno;
        if (yesORno == "yes" || yesORno == "Yes" || yesORno == "y" || yesORno == "Y" || yesORno == "1")
        {
            if (bullets.getBulletsCount() > 10)
            {
                bullets.subBulletsCount(10);
                puzzlesResult = doPuzzles();
                if(puzzlesResult == true)
                {
                    food.bearFood();
                }
            }
            else
                cout << "You have no enough bullets! You can't hunt it." << endl;
        }
        else
        {
            cout << "No huntings for today I guess!" << endl;
        }
    }
    else if (probability > 95 && probability <= 100)
    {
        cout << "You got lucky! You encountered a moose! Do you want to hunt: (1) Yes, (2) No " ;
        cin >> yesORno;
        if (yesORno == "yes" || yesORno == "Yes" || yesORno == "y" || yesORno == "Y" || yesORno == "1")
        {
            if (bullets.getBulletsCount() > 10)
            {
                bullets.subBulletsCount(12);
                puzzlesResult = doPuzzles();
                if(puzzlesResult == true)
                {
                    food.mooseFood();
                }
            }
            else
                cout << "You have no enough bullets! You can't hunt it." << endl;
        }
        else
        {
            cout << "No huntings for today I guess!" << endl;
        }
    }
}

void OregonTrail::afterHunting()
{
    int eatQuality;
    int pounds;
    cout << endl << "The hunting finished. How well do you want to eat?" << endl;
    cout << "1. Poorly 2. Moderately 3. Well : Your choice? ";
    cin >> eatQuality;
    if (eatQuality == 1)
    {
        pounds = numPlayers * 2;
        food.eatenFood(pounds);
    }
    else if (eatQuality == 2)
    {
        pounds = numPlayers * 3;
        food.eatenFood(pounds);
    }
    else if (eatQuality == 3)
    {
        pounds = numPlayers * 5;
        food.eatenFood(pounds);
    }
    
    if (food.getTotalFood() > 1000)
    {
        cout << "The wagon cannot hold more than 1,000 lbs. So you have to cut the food at 1,000 lbs." << endl;
        food.cutTotalFood(1000);
    }
}
//void statusUpdate();
//int hunt() {return food;};
//void misfortunes();
//void raiderAttack();
//bool puzzles();


