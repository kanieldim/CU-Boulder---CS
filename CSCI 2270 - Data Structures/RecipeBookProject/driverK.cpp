  #include "recipeBookK.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
// you may include more libraries as needed

using namespace std;

string toUpper(string word){
  int L = word.length();
  for(int i = 0; i< L; i++){
    word[i] = toupper(word[i]);
  }
  return word;
}

void menu()
{
  cout << "============Main Menu============" << endl;
  cout << "1. Print list of recipe" << endl;
  cout << "2. Search by name of the recipe" << endl;
  cout << "3. Search by ingredient on hand" << endl;
  cout << "4. Search by meal type (breakfast, lunch, dinner)" << endl;
  cout << "5. Search by difficulty level (Level 1, 2, or 3)" << endl;
  cout << "6. Print best match" << endl;
  cout << "7. Add your own recipe" << endl;
  cout << "8. Quit" << endl;
}



int main(int argc, char *argv[])
{
  string choice;
  string word;
  string tempName;
  string tempMainIngredient;
  string tempIng2;
  string tempIng3;
  string tempIng4;
  int tempCookTime;
  int tempDifficulty;
  int tempNumIng;
  string tempMealType;
  string searchingN;
  string searchingI;
  string searchingM;
  int searchingD;

  ifstream inFile;
  inFile.open(argv[1]);

  RecipeTable byName(100);
  RecipeTable byIngredient(100);
  RecipeTable L1(100);
  RecipeTable L2(100);
  RecipeTable L3(100);
  RecipeTable breakfast(100);
  RecipeTable lunch(100);
  RecipeTable dinner(100);

  if (inFile.is_open())
  {
    while (inFile.peek() != EOF)
    {
      getline(inFile, word, ',');
      tempName = toUpper(word);

      getline(inFile, word, ',');
      tempMainIngredient = toUpper(word);

      getline(inFile, word, ',');
      tempIng2 = toUpper(word);

      getline(inFile, word, ',');
      tempIng3 = toUpper(word);

      getline(inFile, word, ',');
      tempIng4 = toUpper(word);

      getline(inFile, word, ',');
      tempCookTime = stoi(word);

      getline(inFile, word, ',');
      tempDifficulty = stoi(word);

      getline(inFile, word, ',');
      tempNumIng = stoi(word);

      getline(inFile, word, '\n');
      tempMealType = toUpper(word);


      byName.addRecipeForName(tempName, tempMainIngredient, tempIng2, tempIng3, tempIng4, tempCookTime, tempDifficulty, tempNumIng, tempMealType);
      byIngredient.addRecipeForIngredient(tempName, tempMainIngredient, tempIng2, tempIng3, tempIng4, tempCookTime, tempDifficulty, tempNumIng, tempMealType);

      if(tempDifficulty == 1){
        L1.addRecipeForDiff(tempName, tempMainIngredient, tempIng2, tempIng3, tempIng4, tempCookTime, tempDifficulty, tempNumIng, tempMealType);
      }
      else if(tempDifficulty == 2){
        L2.addRecipeForDiff(tempName, tempMainIngredient, tempIng2, tempIng3, tempIng4, tempCookTime, tempDifficulty, tempNumIng, tempMealType);
      }
      else if(tempDifficulty == 3){
        L3.addRecipeForDiff(tempName, tempMainIngredient, tempIng2, tempIng3, tempIng4, tempCookTime, tempDifficulty, tempNumIng, tempMealType);
      }


      if(tempMealType == "BREAKFAST"){
        breakfast.addRecipeForMeal(tempName, tempMainIngredient, tempIng2, tempIng3, tempIng4, tempCookTime, tempDifficulty, tempNumIng, tempMealType);
      }

      else if (tempMealType == "LUNCH"){
        lunch.addRecipeForMeal(tempName, tempMainIngredient, tempIng2, tempIng3, tempIng4, tempCookTime, tempDifficulty, tempNumIng, tempMealType);
      }

      else if (tempMealType == "DINNER"){
        dinner.addRecipeForMeal(tempName, tempMainIngredient, tempIng2, tempIng3, tempIng4, tempCookTime, tempDifficulty, tempNumIng, tempMealType);
      }
    }
  }


  while (choice != "8")
  {
    menu();
    getline(cin, choice);
    switch (stoi(choice))
    {
      case 1: // print a list of recipe book
      {
        cout << "-------------------- Recipe Index --------------------"<< endl;
        byName.skimBook();
        //print a list of recipe names available in the cookbook
        cout << "------------------------------------------------------"<< endl;
        break;

      }
      case 2: // search name
      {
        cout<< "What dish are you searching for? ";
        getline(cin, searchingN);
        cout << endl;
        //print recipe that the pointer is pointing to
        RecipeItem* found=byName.searchName(toUpper(searchingN));
        if( found==nullptr ){
          cout<< "Dish not found in recipe book."<< endl;
          break;
        }
        else{
          cout << found -> name << endl;
          //print the information for the found RecipeItem.
        }
        break;
      }
      case 3: //search ingredient
      {
        cout << "What ingredient do you have? ";
        getline(cin, searchingI);
        cout << endl;

        RecipeItem* found=byName.searchName(toUpper(searchingI));
        if(found == nullptr){
          cout<< "Dish not found in recipe book."<< endl;
          break;
        }
        else{
          while (found != nullptr){


          }
          //print the information for the found RecipeItem.
        }
       //call print by ingredient function
        break;
      }
      case 4: //sort by meal type
      {
        string type, type1;
        cout << "What type of meal? (breakfast, lunch, or dinner) ";
        getline(cin, type);
        type1 = toUpper(type);
        cout << endl;


        if(type1 == "BREAKFAST"){
          breakfast.skimBook();
        }
        else if (type1 == "LUNCH"){
          lunch.skimBook();
        }
        else if (type1 == "DINNER"){
          dinner.skimBook();
        }
        else{
          cout << "Invald input!" << endl;
        }

        break;
      }
      case 5: // search difficulty level
      {
        string level;
        int level1;
        cout << "What is the difficulty level? (1, 2, or 3) ";
        getline(cin, level);
        level1 = stoi(level);
        cout << endl;

        if(level1 == 1){
          L1.skimBook();
        }
        else if(level1 == 2){
          L2.skimBook();
        }
        else if(level1 == 3){
          L3.skimBook();
        }
        else{
          cout << "Invalid input!" << endl;
        }

        break;
      }
      case 6: // get best match
      {
        //ask user input for difficulty level
        //print breakfast lunch or dinner hash table

        break;
      }
      case 7: // Add your own recipe
      {
        string one, two, three, four, five, six, seven, eight, nine;
        string one1, two2, three3, four4, five5, nine9;
        int six6, seven7, eight8;

        cout << "What is your dish called? ";
        getline(cin, one);
        one1 = toUpper(one);
        cout << endl;

        cout << "What is the main ingredient? (Required) ";
        getline(cin, two);
        two2 = toUpper(two);
        cout << endl;

        cout << "What is the side ingredient? (Insert none if it is optional) ";
        getline(cin, three);
        three3 = toUpper(three);
        cout << endl;

        cout << "What is the side ingredient? (Insert none if it is optional) ";
        getline(cin, four);
        four4 = toUpper(four);
        cout << endl;

        cout << "What is the side ingredient? (Insert none if it is optional) ";
        getline(cin, five);
        five5 = toUpper(five);
        cout << endl;

        cout << "What is the number of ingredient? (Insert none if it is optional) ";
        getline(cin, eight);
        eight8 = stoi(eight);
        cout << endl;

        cout << "What is the cooking time? ";
        getline(cin, six);
        six6 = stoi(six);
        cout << endl;

        cout << "What is the difficulty? (Level 1, 2, or 3) ";
        getline(cin, seven);
        seven7 = stoi(seven);
        cout << endl;

        cout << "What is the meal type? (breakfast, lunch, or dinner) ";
        getline(cin, nine);
        nine9 = toUpper(nine);
        cout << endl;


        byName.addRecipeForName(one1, two2, three3, four4, five5, six6, seven7, eight8, nine9);
        byIngredient.addRecipeForIngredient(one1, two2, three3, four4, five5, six6, seven7, eight8, nine9);

        if(seven7 == 1){
          L1.addRecipeForDiff(one1, two2, three3, four4, five5, six6, seven7, eight8, nine9);
        }
        else if(seven7 == 2){
          L2.addRecipeForDiff(one1, two2, three3, four4, five5, six6, seven7, eight8, nine9);
        }
        else if(seven7 == 3){
          L3.addRecipeForDiff(one1, two2, three3, four4, five5, six6, seven7, eight8, nine9);
        }

        if(nine9 == "BREAKFAST"){
          breakfast.addRecipeForMeal(one1, two2, three3, four4, five5, six6, seven7, eight8, nine9);
        }
        else if (nine9 == "LUNCH"){
          lunch.addRecipeForMeal(one1, two2, three3, four4, five5, six6, seven7, eight8, nine9);
        }
        else if (nine9 == "DINNER"){
          dinner.addRecipeForMeal(one1, two2, three3, four4, five5, six6, seven7, eight8, nine9);
        }

        cout << "New Recipe Added!" << endl;

        break;

      }
      case 8: // quit
      {
        cout << "Goodbye! See you again!" << endl;
        break;
      }
      default:
      {
        cout << "Invalid input!" << endl;
      }
    }

  }


  return 0;
}





