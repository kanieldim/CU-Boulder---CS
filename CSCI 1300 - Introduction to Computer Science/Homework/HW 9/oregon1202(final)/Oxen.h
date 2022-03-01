#include <iostream>

#ifndef OXEN_H
#define OXEN_H

class Oxen
{
    int numWagon;
    int numOxen;
    int numYokes;
    
    int numCategory;
    int numCategoryOxen;
    float priceOxen;
    float categoryBill;
    float currentBill;

    
    public:
    
    Oxen();
    void setNumWagon(int);
    void addNumWagon(int);
    void brokenWagon();
    void setNumYokes(int);
    void addNumYokes(int);
    void brokenYokes();
    void setNumOxen(int);
    void addNumOxen(int);
    void deadOxen();
    
    float getCurrentBill() { return currentBill; };
    float getPriceOxen() { return priceOxen; };
    void resetCategoryBill(void);

    void printOxenBill();
    
};

#endif
