#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>
#include "Date.h"
#include "Bullets.h"
#include "Food.h"
#include "MiscSupplies.h"
#include "Oxen.h"
#include "Player.h"
#include "Distance.h"
#include "OregonTrail.h"

using namespace std;

void startingMenu()
{
    int numNames = 1;
    string playerName;
    
    cout << "What is your name?: ";
    cin >> playerName;
    cout << "Please enter the names of your companions below: " << endl;
    while (numNames < 5)
    {
        cout << numNames << ". ";
        cin >> playerName;
        numNames++;
    }
    
    cout << endl;
    cout << "You are starting at mile: 0." << endl;
    cout << "There are 2040 that you must travel to reach your destination." << endl;
}

void store()
{
    cout << "Welcome to the Store!" << endl;
    cout << "YOU HAD SAVED $1200 TO SPEND FOR THE TRIP, AND YOU'VE INITIALLY PAID $200 FOR A WAGON. YOU WILL NEED TO SPEND THE REST OF YOUR MONEY ON THE FOLLOWING ITEMS:" << endl;
    cout << 
    
    
    Welcome to the Store!

- OXEN. YOU CAN SPEND $100-$200 ON YOUR TEAM. THE MORE YOU SPEND, THE FASTER YOU'LL GO BECAUSE YOU'LL HAVE BETTER ANIMALS
- FOOD. THE MORE YOU HAVE, THE LESS CHANCE THERE IS OF GETTING SICK
- BULLETS - $2 BUYS A BELT OF 20 BULLETS. YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS AND BANDITS, AND FOR HUNTING FOOD
- MISCELLANEOUS SUPPLIES. THIS INCLUDES MEDICINE AND OTHER THINGS YOU WILL NEED FOR SICKNESS AND EMERGENCY REPAIRS
YOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP, OR YOU CAN SAVE SOME OF YOUR CASH TO SPEND AT FORTS ALONG THE WAY WHEN YOU RUN LOW. HOWEVER, ITEMS COST MORE AT THE FORTS. YOU CAN ALSO GO HUNTING ALONG THE WAY TO GET MORE FOOD.
Right now you have: $1000.
}

int main()
{
    startingMenu();
    
    
    
    
    
    
    
    
    
    
    
    
}


