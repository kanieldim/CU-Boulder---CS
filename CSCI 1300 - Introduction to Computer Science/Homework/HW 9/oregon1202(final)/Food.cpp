#include "Food.h"

using namespace std;

Food::Food()
{
    totalFood = 0;
    randomFood = 0;
    poundsFood = 0;
    numCategory = 0;
    priceFood = 0.0;
    categoryBill = 0.0;
    currentBill = 0.0;
}

void Food::setTotalFood(int pounds)
{
    poundsFood += pounds;
    numCategory = pounds;
    priceFood += (0.5 * pounds);
    categoryBill = pounds * 0.5;
    currentBill += categoryBill;
    //totalCash = totalCash - currentBill;
    totalFood += poundsFood;
}

void Food::cutTotalFood(int pounds)
{
    totalFood = pounds;
}

void Food::addFood(int MoreFood)
{
    totalFood = totalFood + MoreFood;
}

void Food::eatenFood(int pounds)
{
    totalFood = totalFood - pounds;
}

void Food::restFood(int numPlayers, int numDays)
{
    totalFood = totalFood - 3 * numPlayers * numDays;
}

void Food::rabbitFood()
{
    totalFood = totalFood + 2;
}

void Food::foxFood()
{
    totalFood = totalFood + 5;
}

void Food::deerFood()
{
    randomFood = rand()%26 + 30;
    totalFood = totalFood + randomFood;
}

void Food::bearFood()
{
    randomFood = rand()%251 + 100;
    totalFood = totalFood + randomFood;
}

void Food::mooseFood()
{
    randomFood = rand()%301 + 300;
    totalFood = totalFood + randomFood;
}

void Food::printFoodBill()
{
    cout << " - " << "Food " << "\t " << poundsFood << "lbs\t" << " $" << priceFood << endl;
}

void Food::resetCategoryBill()
{
    categoryBill = 0.0;
    numCategory = 0;
}
