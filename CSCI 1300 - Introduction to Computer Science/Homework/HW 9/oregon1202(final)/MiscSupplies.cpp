#include "MiscSupplies.h"

using namespace std;

MiscSupplies::MiscSupplies()
{
    numParts = 0;
    numKits = 0;
    
    numCategoryParts = 0;;
    priceParts = 0.0;
    categoryBill = 0.0;
    
    numCategoryKits = 0;
    priceKits = 0.0;
    currentBill = 0.0;
}

void MiscSupplies::addNumParts(int numOfParts)
{
    numParts = numParts + numOfParts;
}

void MiscSupplies::addNumKits(int numOfKits)
{
    numKits = numKits + numOfKits;
}

void MiscSupplies::setNumParts(int parts)
{
    numParts += parts;
    numCategoryParts = parts;
    priceParts += (parts * 20.0);
    categoryBill = parts * 20.0;
    //currentBill += categoryBill;
    //totalCash -= currentBill;
}

void MiscSupplies::setNumKits(int kits)
{
    numKits += kits;
    numCategoryKits = kits;
    priceKits += (kits * 25.0);
    categoryBill += kits * 25.0;
    currentBill += categoryBill;
    //totalCash -= currentBill;
}

void MiscSupplies::resetCategoryBill()
{
    categoryBill = 0.0;
    numCategoryKits = 0;
    numCategoryParts = 0;
}

void MiscSupplies::printMiscBill(void)
{
    cout << " - " << "Parts " << "\t " << numParts << " ea\t" << " $" << priceParts << endl;
    cout << " - " << "M. Kits " << "\t " << numKits << " ea\t" << " $" << priceKits << endl;
}

