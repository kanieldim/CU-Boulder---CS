// CSCI1300 Fall 2018
// Author: Daniel Kim
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/kanieldim/csci1300
// Homework 6

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX_BOOK_COUNT 50   // defining the maximum number of books stored in the books file
#define MAX_USER_COUNT 100  // defining the maximum number of read/review-users stored in the ratings file
#define MAX_RATING_COUNT 50 // defining the maximum number of book-ratings stored in the ratings file
#define YES 1
#define NO 0

/* split function
 * the function to split the given string into array of string with respect to a delimiter
 *
 * @param : string , the string we are going to split
 * @param : char, the delimiter
 * @param : string array, the array of string we save after spliting
 * @param : int, size of the  indicates the maximum number of split-apart string pieces
 */
int split (string str, char c, string array[], int size)
{
    if (str.length() == 0) {
        return 0;
    }
    string word = "";
    int count = 0;
    str = str + c;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            if (word.length() == 0)
                continue;
            array[count++] = word;
            word = "";
        } else {
            word = word + str[i];
        }
    }
    return count ;
}

/* readBooks function
 * the function reads a book file from the text into book and author arrays
 *
 * @param: string, the name of the file to be read
 * @param: string array, titles
 * @param: string array, authors
 * @param: int, the number of books currently stored in the arrays
 * @param: int, capacity of the authors/titles arrays [assume to be 50]
 * @return: the total number of books in total
 */

//////////////////////////////////////////////////////////////////////////
// ToDo: implement readBooksfunction
int readBooks (string nameFile, string titles[], string authors[], int nofBooks, int capacity)
{
    
    ifstream inFile;
    int bookCnt = 0;
    int columns = 0;
    string line = "";
    string authorTitle[2];
    
    inFile.open(nameFile);
    
    if( !inFile.is_open() ) {
        return -1;
    }
    
    while ( getline(inFile, line) ) {
        columns = split ( line, ',', authorTitle, 2 ); // spliting the line to author and title by using comma delimiter
        authors[bookCnt] = authorTitle[0]; // storing an author to the array, authors
        titles[bookCnt] = authorTitle[1];  // storing a title to the array, titles

        bookCnt++;
    }
    
    inFile.close();
    
    return bookCnt; // returing the number of books stored in the books file
}
//////////////////////////////////////////////////////////////////////////


/* readRatings function
 * Read the user ratings from the file and store them
 * into users array and ratings array
 *
 * @param: string, the name of the file to be read
 * @param: string array, usernames
 * @param: 2D int array, list of ratings for each user (first index specifies user)
 * @param: int, the number of users currently stored in the array
 * @param: int, row capacity of the 2D array (convention: array[row][column]) [assume to be 100]
 * @param: int, column capacity of the 2D array [assume to be 50]
 * @return: the number of users in total
 */

//////////////////////////////////////////////////////////////////////////
// ToDo: implement readRatings function
int readRatings (string nameFile, string userNames[], int listRatings[MAX_USER_COUNT][MAX_RATING_COUNT], int nofUsers, int rowCapacity, int columnCapacity )
{
    ifstream inFile;
    int userCnt = 0;
    int columns = 0;
    int lists;
    string line = "";
    string userRating[2];
    string ratings[MAX_USER_COUNT];
    string ratingStr[MAX_RATING_COUNT];
    
    inFile.open(nameFile);
    
    if( !inFile.is_open() ) {
        return -1;
    }
    while ( getline(inFile, line) ) {
        columns = split ( line, ',', userRating, 2 ); // spliting the line user's name and the list of ratings
        userNames[userCnt] = userRating[0]; // storing a user name to the array, userNames
        ratings[userCnt] = userRating[1];   // storing a user's ratings-list to the array, ratings
        cout << userRating[0] << "..." << endl;
        lists = split ( ratings[userCnt], ' ', ratingStr, MAX_RATING_COUNT ); // spliting the ratings-list in the array, ratingStr
        for ( int i = 0; i < lists; i++ ) {
            listRatings[userCnt][i] = stoi(ratingStr[i]); // converting each ratingStr to a rating in the array, listRatings
        }
        userCnt++;
    }
    
    inFile.close();
    
    
    
    return userCnt; // returing the number of read/reviewed users stored in the ratings file
}
//////////////////////////////////////////////////////////////////////////

/* printAllBooks function
 * the function display the contents of the books
 *
 * @param: string array, titles
 * @param: string array, authors
 * @param: int, the number of books currently stored in the arrays
 * @return: no return
 */

//////////////////////////////////////////////////////////////////////////
// ToDo: implement printAllBooks function
void printAllBooks ( string titles[], string authors[], int bookCount )
{
    
    if ( bookCount == 0 )
    {
        cout << "No books are stored" << endl;
    }
    
    cout << "Here is a list of books" << endl;
    for ( int i = 0; i < bookCount; i++ )
    {
        cout << titles[i] << " by " << authors[i] << endl;
    }
    
}

/* getUserReadCount function
 * the function determines how many books a particular user has read and reviewed
 *
 * @param: string, a particular user name for whom we want a read/reviewed count
 * @param: string array, all users, userNames
 * @param: 2D int array, list of all ratings, listRatings, one row for each user
 * @param: int, the number of users currently stored in the array
 * @param: int, the number of books currently accounted for in the array
 * @return: int, the number of books read/reviewed by the specified user
 */

//////////////////////////////////////////////////////////////////////////
// ToDo: implement getUserReadCount function
int getUserReadCount ( string aUserName, string userNames[], int listRatings[MAX_USER_COUNT][MAX_RATING_COUNT], int userCount, int bookCount )
{
    int bookCntBytheUser = 0;
    
    for ( int i = 0; i < userCount; i++ )
    {
        if ( userNames[i].compare(aUserName) == 0 ) // searching a particular user in the read/reviewed users
        {
            for ( int n = 0; n < bookCount; n++ ) // finding the number of books the user rated
            {
                if ( listRatings[i][n] > 0 ) // rating 0 : Did not read, rating 1 ~ 5 : read and reviewed
                {
                    bookCntBytheUser++;
                }
            }
        }
        else
        {
            return -1;
        }
    }
    
    return bookCntBytheUser;
}

double calcAverage (string aBookTitle, string titles[], int listRatings[MAX_USER_COUNT][MAX_RATING_COUNT], int userCount, int bookCount)
{
    int readCount = 0;
    int ratingSum = 0;
    double avgRating = 0.0;
    
    if (userCount == 0)
    {
        return -1;
    }
    
    for (int i = 0; i < bookCount; i++)
    {
        if (titles[i].compare(aBookTitle) == 0)
        {
            for (int n = 0; n < userCount; n++)
            {
                ratingSum = ratingSum + listRatings[n][i]; // summing up all the users' rating for a particular book
                // cout << listRatings[n][i] << " ";
                if (listRatings[n][i] > 0) // summing up the read/reviewed users
                {
                    readCount++;
                }
            }
            avgRating = ratingSum / (double) readCount; // calculating the average rating
            // cout << "The average rating for " << aBookTitle << " is " << avgRating << endl;
            break;
        }
    }
    
    return avgRating;
}

/* calcAvgRating function
 * the function calculates the average rating for a particular book
 *
 * @param: string, a particular book title for whom we want the average rating
 * @param: string array, all book titles, titles
 * @param: 2D int array, list of all ratings, listRatings, one row for each user
 * @param: int, the number of users currently stored in the array
 * @param: int, the number of books currently accounted for in the array
 * @return: int, the average rating of the specified book title
 */

//////////////////////////////////////////////////////////////////////////
// ToDo: implement calcAvgRating function

//////////////////////////////////////////////////////////////////////////

/* displayMenu:
 * displays a menu with options
 * DO NOT MODIFY THIS FUNCTION
 */
void displayMenu(){
    cout << "Select a numerical option: " << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Read book file" << endl;
    cout << "2. Read user file" << endl;
    cout << "3. Print book list" << endl;
    cout << "4. Find number of books user rated" << endl;
    cout << "5. Get average rating" << endl;
    cout << "6. Quit" << endl;
    
}


int main(int argc, char const *argv[]) {
    string choice;
    int booksFileOpened = NO;
    int ratingsFileOpened = NO;
    int numBooks = 0;
    int numUsers = 0;
    string booksFILE;
    string titles[MAX_BOOK_COUNT];
    string authors[MAX_BOOK_COUNT];
    string ratingsFILE;
    string userNames[MAX_USER_COUNT];
    int listRatings[MAX_USER_COUNT][MAX_RATING_COUNT];
    string aUserName;
    int numReads = 0;
    string nothing = "";
    string aBookTitle;
    double avgRating = 0.0;

    
    while (choice != "6") {
        displayMenu();
        getline(cin, choice);
        switch (stoi(choice)) {
            case 1:
                // read book file
                cout << "Enter a book file name: " << endl;
                
                //////////////////////////////////////////////////////////////////////////
                getline(cin, booksFILE);
                numBooks = readBooks ( booksFILE, titles, authors, MAX_BOOK_COUNT, MAX_BOOK_COUNT );
                if ( numBooks == -1 )
                {
                    booksFileOpened = NO;
                    cout << "No books saved to the database" << endl;
                }
                else
                {
                    booksFileOpened = YES;
                    cout << "Total books in the database: " << numBooks << endl;
                }
                //////////////////////////////////////////////////////////////////////////
                
                
                cout << endl;
                break;
                
            case 2:
                // read user file
                cout << "Enter a rating file name: " << endl;
                
                //////////////////////////////////////////////////////////////////////////
                getline(cin, ratingsFILE);
                numUsers = readRatings ( ratingsFILE, userNames, listRatings, MAX_USER_COUNT, MAX_USER_COUNT, MAX_RATING_COUNT );
                if ( numUsers == -1 )
                {
                    ratingsFileOpened = NO;
                }
                else
                {
                    ratingsFileOpened = YES;
                }
                //////////////////////////////////////////////////////////////////////////
                
                cout << "Total users in the database: " << numUsers << endl;
                cout << endl;
                break;
                
            case 3:
                // print the list of the books
                
                //////////////////////////////////////////////////////////////////////////
                if ( booksFileOpened == NO )
                    cout << "No books are stored" << endl;
                else
                    printAllBooks ( titles, authors, numBooks );
                //////////////////////////////////////////////////////////////////////////
                
                cout << endl;
                break;
                
            case 4:
                cout << "Enter username: " << endl;
                
                // find the number of books user read
                
                
                //////////////////////////////////////////////////////////////////////////
                getline( cin, aUserName );
                numReads = getUserReadCount ( aUserName, userNames, listRatings, numUsers, MAX_RATING_COUNT );
                if ( numReads == -1 )
                {
                    cout << aUserName << " rated 0 books" << endl;
                }
                // else if (numReads == nothing)
                //     cout << aUserName << " rated 0 books" << endl;
                else
                {
                    cout << aUserName << " rated " << numReads << " books" << endl;
                }
                //////////////////////////////////////////////////////////////////////////
                
                cout << endl;
                break;
                
           case 5:
                // get the average rating of the book
                cout << "Enter book title: " << endl;
                
                //////////////////////////////////////////////////////////////////////////
                getline(cin, aBookTitle );
                avgRating = calcAverage ( aBookTitle, titles, listRatings, numUsers, numBooks );
                
                if ( avgRating == -1 )
                    cout << "The book (" << aBookTitle << ") does not exist in the database" << endl;
                else
                    cout << "The average rating for " << aBookTitle << " is " << setprecision(3) << avgRating << endl;
                aBookTitle = "";
                //////////////////////////////////////////////////////////////////////////
                
                cout << endl;
                break;

            case 6:
                // quit
                cout << "good bye!" << endl;
                break;
                
            default:
                cout << "invalid input" << endl << endl;
        }
    }
    
    return 0;
}