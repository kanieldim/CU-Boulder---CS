/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
#include <stack>

// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

int main()
{

  // TODO - Declare a stack to hold the operands
  RPNCalculator rpn;


  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;



  while(true)
  {

    string choice;
    bool yesOrNo;
    float numInput = 0.0;
    float finalResult = 0.0;
    cout << "#> ";
    getline (cin, choice);


        /* TODO
           1. Read input (operators and operands) until you encounter a "="
           2. Use the isNumber function to check if the input is an operand
           3. push all operands to the stack
           4. If input is not an operand, call the compute function to evaluate
              the partial expression
        */


    yesOrNo = isNumber(choice);
    if (yesOrNo == true)
    {
      numInput = stof(choice);
      rpn.push(numInput);
    }

    else if (yesOrNo == false)
    {
      if (choice == "+" || choice == "*")
      {
        rpn.compute(choice);
      }
    }
    if (choice == "=")
    {
      Operand *temp = rpn.getStackHead();
      if (temp == nullptr)
      {
        cout << "No operands: Nothing to evaluate" << endl;
        break;
      }
      else
      {
        if (rpn.peek() -> next == nullptr)
        {
          finalResult = rpn.peek() -> number;
          cout << finalResult << endl;
          break;
        }
        else
        {
          cout << "Invalid expression" << endl;
          break;
        }
      }


    }

    /* TODO - If the stack is empty then print "No operands: Nothing to evaluate" */

  }


  /* TODO - Validate the expression
      1. If valid then print the result
      2. Else, print "Invalid expression"*/

  return 0;
}
