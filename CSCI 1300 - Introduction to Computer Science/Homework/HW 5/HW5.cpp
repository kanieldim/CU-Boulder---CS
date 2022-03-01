// Daniel Kim: CS1300 Fall 2018
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/kanieldim/csci1300
// Homework 5

#include <iostream>

using namespace std;

/*
    Algorithm: Find the best matching genome sequence for a given bacerial sequence 
            1. Create obtaining sequence length function (obtainingSeqLength) to determine the length to make sure lengths of both sequences match
                    - If sequence lengths do not equal to each other return -1 (LENGTH_MISMATCH)
                    - If sequence lengths are empty return 0 (EMPTY)
                    - Return sequence length
            2. Create similarity score to get in order to compare other genome
                    - Recall to obtaining sequence length function if following test cases are true
                    - Set up for loop to add hamming distance if two sequences are different
                    - Calculate the score by ((sequence length - hamming distance) / sequence length)
                    - Make sure the result is in double
                    - Return the score
            3. Create the highest similarity function to get the best result from similarity score fucntion
                    - Create for loop for genome 1, 2, 3 
                    - Recall similarity score function to get the result for each genome
                    - If length of sequnce DNA is less than the length of sequnce bacteria, break
                    - return the highest score
            4. Create void analyzer fucntion to run the program
                    - Make sure that genome 1, 2, 3, and sequence bacteria are not empty to run the program
                    - Make sure that sequence length for all genome 1, 2, 3 match
                    - Make sure that sequence length is bigger than genome length
                    - Make for loop statements to find the best match out of genome 1, 2, 3
                    - If best count is 0, make sure it prints no genome is the best match
    Void analyzer:                
    Input values : genome 1, 2, 3, sequence bacteria
    Output : result (Best match)
    Return : nothing
*/

#define LENGTH_MISMATCH -1 // define -1 to be more clear
#define EMPTY 0 // define 0 to be more clear

int obtainingSeqLength (string seqFirst, string seqSecond) // fucntion for obtaining sequence length
{
    int seqLength, lengthSecond; // add variables
    
    if ((seqLength = seqFirst.length()) != (lengthSecond = seqSecond.length())) // if the length from both sequence does not match return -1
    {
        return LENGTH_MISMATCH; // return
    }
    else if ((seqLength == 0) || (lengthSecond == 0)) // if the length of both sequences are empty return 0;
    {
        return EMPTY; // return
    }
    
    return seqLength; // return
}

double simScore (string seqFirst, string seqSecond) // fucntion for similarity score
{
    int seqLength; // add variables
    int hammingDistance = 0;
    double theScore;
    
    seqLength = obtainingSeqLength(seqFirst, seqSecond); // recall function to see the length requirements
    
    if((seqFirst.length() == 0) || (seqSecond.length() == 0)) // return 0 if sequence is empty
    {
        return EMPTY;
    }
    if ((seqFirst.length()) != (seqSecond.length())) // return 0 if sequence does not match
    {
        return EMPTY;
    }
    
    for (int i = 0; i < seqLength; i++) // set up for loop to find hamming distance
    {
        if (seqFirst[i] != seqSecond[i])
        {
            hammingDistance++;
        }
    }
    
    theScore = ((double) seqLength - hammingDistance) / (double) seqLength; // calculate the score
    
    return theScore; // return
    
}

double theHighestSimilarity (string seqDNA, string seqBacteria) // fucntion to find the highest similarity from the scores above
{
    int i; // add variables
    int seqBacLength;
    double theHighestScore = 0.0;
    double theScore;
    
    seqBacLength = seqBacteria.length(); // set seqBacLength as length()
    
    for (i = 0; i < seqDNA.length(); i++) // set for loop statement for each genome
    {
        theScore = simScore(seqDNA.substr(i, seqBacLength), seqBacteria); // recall similarity score function
        
        if (theHighestScore < theScore) // if the highest score is less than the score
        {
            theHighestScore = theScore; // set highest score as the score
        }
        
        if ((seqDNA.length() - (i + 1)) < seqBacLength) // if sequence DNA is less than sequence bacteria length
        {
            break; // break
        }
    }
    
    return theHighestScore; // return
}

void analyzer (string genome1ST, string genome2ND, string genome3RD, string seqBacteria) // void function analyzer program
{
    int i = 0, bestCount = 0; // add variables
    int seqLength;
    double theHighestScore[3] = {0.0, 0.0, 0.0}; // array for similarity scores from genome 1, 2, 3
    double theBestMatch = 0.0;
    
    if (genome1ST.length() == EMPTY || genome2ND.length() == EMPTY || genome3RD.length() == EMPTY || seqBacteria.length() == EMPTY) // if genome 1, 2, 3, or sequence bacteria is empty
    {
        cout << "Genome and sequence cannot be empty." << endl; // result
        return;
    }
    
    if ((seqLength = obtainingSeqLength(genome1ST, genome2ND)) == LENGTH_MISMATCH) // if genome 1 and 2 length do not match 
    {
        cout << "Genome length does not match." << endl; // result 
        return;
    }
    else if ((seqLength = obtainingSeqLength(genome1ST, genome3RD)) == LENGTH_MISMATCH) // if genome 1 and 3 length do not match
    {
        cout << "Genome length does not match." << endl; // result
        return;
    }
    // Don't have to make else if statement for genome 2 and 3 because genome 1 = 2 and genome 1 = 3 means genome 2 = 3
    if (seqLength < seqBacteria.length()) // if sequence length smaller than genome length
    {
        cout << "Sequence length must be smaller than genome length." << endl; // result
        return;
    }
    
    theHighestScore[0] = theHighestSimilarity(genome1ST, seqBacteria); // recall the highest similarity for genome 1
    theHighestScore[1] = theHighestSimilarity(genome2ND, seqBacteria); // recall the highest similarity for genome 2
    theHighestScore[2] = theHighestSimilarity(genome3RD, seqBacteria); // recall the highest similarity for genome 3

    for (i = 0; i < 3; i++) // for loop statement 
    {
        if ((theBestMatch < theHighestScore[i]) && (theHighestScore[i] > 0)) // if highest score is bigger than biggest match and bigger than 0
        {
            theBestMatch = theHighestScore[i]; // set highest score to best match
        }
    }
    
    for (i = 0; i < 3; i++) // for loop statement
    {
        if ((theBestMatch == theHighestScore[i]) && theHighestScore[i] > 0)
        {
            bestCount++;
            cout << "Genome " << i + 1 << " is the best match." << endl; // print result
        }
    }
    
    if (bestCount == 0) // if best count is 0
    {
        cout << "No genome is the best match" << endl; // result
        return;
    }
}

int main()
{
    analyzer("","TGC","","TTA");
    cout << endl;
    
    analyzer("AAG","TGC","GATTACA","TAC");
    cout << endl;
    
    analyzer("TTC","GCC","TCT","");
    cout << endl;
    
    analyzer("AC","AC","AC","AC");
    cout << endl;
    
    analyzer("TAAGGCA", "TCTGGGC", "CTAATAT", "AAG");
    cout << endl;
    
    analyzer("TAAGGCA", "TACCTAC", "AGCCAGA", "TCT");
    cout << endl;

    return 0;
}