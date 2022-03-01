#include <iostream>

#ifndef FOOD_H
#define FOOD_H

class Food
{
    int totalFood;
    int randomFood;
    
    int poundsFood;
    int numCategory;
    float priceFood;
    float categoryBill;
    float currentBill;
    
    public:
    
    Food();
    int getTotalFood() {return totalFood;};
    void setTotalFood(int);
    void cutTotalFood(int);
    void addFood(int);
    void eatenFood(int);
    void restFood(int, int);
    void rabbitFood();
    void foxFood();
    void deerFood();
    void bearFood();
    void mooseFood();
    
    float getCurrentBill() { return currentBill; };
    float getPriceFood() { return priceFood; };
    void resetCategoryBill(void);
    void printFoodBill();
};

#endif
