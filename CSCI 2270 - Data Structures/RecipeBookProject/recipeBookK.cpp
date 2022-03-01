#include "recipeBookK.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

//Constructor
RecipeTable::RecipeTable(int recipeTableSize)
{
  tableSize = recipeTableSize;
  recipeTable = new RecipeItem *[tableSize];
  for (int i = 0; i < tableSize; i++)
  {
    recipeTable[i] = NULL;
  }
}

//Destructor
RecipeTable::~RecipeTable()
{
  for (int i = 0; i < tableSize; i++)
  {
    RecipeItem *temp = recipeTable[i];
    while (temp != NULL)
    {
      RecipeItem *a = temp;
      temp = temp->next;
      delete a;
    }
  }
  delete recipeTable;
}

/*
Function: createRecipeNode
Adds a new struct RecipeItem 
*/

RecipeItem *RecipeTable::createNode(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType, RecipeItem *next)
{
  RecipeItem *nr = new RecipeItem;
  nr->name = name;
  nr->mainIngredient = mainIngredient;
  nr->ing2 = ing2;
  nr->ing3 = ing3;
  nr->ing4 = ing4;
  nr->cookTime = cookTime;
  nr->difficulty = difficulty;
  nr->numIng = numIng;
  nr->mealType = mealType;
  nr->next = NULL;

  return nr;
}
/*
Function: addRecipe
add recipe into the hash table
*/

void RecipeTable::addRecipeForName(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType)
{

  int index = getHash(name); //find the index
  RecipeItem *temp = recipeTable[index];
  RecipeItem *ptr = createNode(name, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType, NULL);
  if (!isInTable(name))
  {
    if (temp != NULL)
    {
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = ptr;
    }
    else
    {

      recipeTable[index] = ptr;

      ptr->next = NULL;
      delete temp;
    }
  }

  else
  {
    // cout << word << " already exists in the recipe book"  endl;
    return;
  }
  return;
}

void RecipeTable::addRecipeForIngredient(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType)
{

  int index = getHash(mainIngredient); //find the index
  RecipeItem *temp = recipeTable[index];
  RecipeItem *ptr = createNode(name, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType, NULL);
  if (!isInTable(name))
  {
    if (temp != NULL)
    {
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = ptr;
    }

    else
    {

      recipeTable[index] = ptr;

      ptr->next = NULL;
      delete temp;
    }
  }

  else
  {
    // cout << name << " already exists in the recipe book"  endl;
    return;
  }
  return;
}

void RecipeTable::addRecipeForMeal(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType)
{

  int index = getHash(mealType); //find the index
  RecipeItem *temp = recipeTable[index];
  RecipeItem *ptr = createNode(name, mainIngredient, ing2, ing3, ing4, cookTime, difficulty, numIng, mealType, NULL);
  if (!isInTable(name))
  {
    if (temp != NULL)
    {
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = ptr;
    }

    else
    {

      recipeTable[index] = ptr;

      ptr->next = NULL;
      delete temp;
    }
  }

  else
  {
    // cout << name << " already exists in the recipe book"  endl;
    return;
  }
  return;
}

void RecipeTable::addRecipeForDiff(string name, string mainIngredient, string ing2, string ing3, string ing4, int cookTime, int difficulty, int numIng, string mealType)
{
  if (!isInTable(name)){
    int index=getHashDiff(difficulty);
    if (recipeTable[index]==NULL){
      RecipeItem* a=createNode(name,mainIngredient,ing2,ing3,ing4,cookTime,difficulty,numIng,mealType,NULL);
      recipeTable[index]=a;
    }
    else{

      RecipeItem* a=recipeTable[index];
      while(a!=NULL){
        a=a->next;
      }
      a=createNode(name,mainIngredient,ing2,ing3,ing4,cookTime,difficulty,numIng,mealType,NULL);
    }
  }
  else{
    cout << "Already in Table!!" << endl;
  }
}
/*
Function: isInTable{
  Returns true if the recipe is in the table and false otherwise.
}

*/
bool RecipeTable::isInTable(string name)
{

  RecipeItem *temp = searchName(name);
  if (temp == nullptr)
  {
    //delete temp;
    return false;
  }
  else
  {
    //delete temp;
    return true;
  }
}


/*
Function: Skim Book
Prints all of the possible recipes, so the user can quickly see options.
*/

void RecipeTable::skimBook()
{
  //cout << "Here are all of the recipes in the book: " << endl;
  for (int i = 0; i < tableSize; i++)
  {
    if (recipeTable[i] != nullptr)
    {
      cout << recipeTable[i] -> name << endl;
      RecipeItem *temp = recipeTable[i];
      while (temp != nullptr)
      {
        cout << temp -> name << endl;
        temp = temp -> next;
      }
    }
  }
}

/*
Function: SearchName
Search the hash table for the parameterized name and returns the RecipeItem with the name.
*/

RecipeItem *RecipeTable::searchName(string name)
{

  int index = getHash(name);

  if (recipeTable[index] != nullptr)
  {
    RecipeItem *temp = recipeTable[index];
    while (temp != nullptr)
    {
      if (temp->name == name)
      {
        return temp;
      }
      else
      {
        temp = temp->next;
      }
    }
  }

  return nullptr;
}

/*
Function: printBestMatch
This function will find the best match dish from user's input
*/
void RecipeTable::printBestMatch()
{

}


/*
Function: printByIngredients
This function will find the ingredient's hash index and print out those recipes with the parameterized ingredient.
*/
void RecipeTable::printByIngredient(string mainIngredient)
{
  int index = getHash(mainIngredient);

  if (recipeTable[index] != nullptr)
  {
    cout << "Here's the list under " << mainIngredient << endl;
    RecipeItem *temp = recipeTable[index];
    while (temp != nullptr)
    {
      
      cout << temp -> name << endl;
      temp = temp -> next;
    }
  }
}

/*
Function: getHash
Finds the index of a certain name/ingredient/difficulty
*/

unsigned int RecipeTable::getHash(string name)
{

  unsigned int hashValue = 5381;
  int length = name.length();
  for (int i = 0; i < length; i++)
  {
    hashValue = ((hashValue << 5) + hashValue) + name[i];
  }
  hashValue %= tableSize;
  return hashValue;
}

unsigned int RecipeTable::getHashDiff(int num){
  return (num%tableSize);
}