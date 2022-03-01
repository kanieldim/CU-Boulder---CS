#include <iostream>

#ifndef MISCSUPPLIES_H
#define MISCSUPPLIES_H

class MiscSupplies
{
    int numParts;
    int numKits;
    
    int numCategoryParts;
    float priceParts;
    float categoryBill;
    
    int numCategoryKits;
    float priceKits;
    float currentBill;

    public:
    
    MiscSupplies();
    void setNumParts(int);
    void addNumParts(int);
    int getNumParts() { return numParts; };
    float getPriceParts() { return priceParts; };
    void setNumKits(int);
    void addNumKits(int);
    int getNumKits() { return numKits; };
    float getPriceKits() { return priceKits; };

    float getCurrentBill() { return currentBill; };
    void resetCategoryBill();
    void printMiscBill();

};

#endif
