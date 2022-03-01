#include <iostream>

#ifndef BULLETS_H
#define BULLETS_H

class Bullets
{
    int totalBoxes;
    int totalBullets;
    
    int boxesBullets;
    int numCategory;
    float priceBullets;
    float categoryBill;
    float currentBill;
    int numBullets;
    
    public:
    
    Bullets();
    void setBoxesCount(int);
    void setBulletsCount(int);
    void addBoxesCount(int);
    void addBulletsCount(int);
    void subBulletsCount(int);
    int getBoxesCount() {return totalBoxes;};
    int getBulletsCount() {return totalBullets;};
    void huntRabbit();
    void huntFox();
    void huntDeer();
    void huntBear();
    void huntMoose();
    
    void setBullets(int);
    float getCurrentBill() { return currentBill; };
    float getPriceBullets() { return priceBullets; }
    void resetCategoryBill();
    void printBulletsBill();

};

#endif
