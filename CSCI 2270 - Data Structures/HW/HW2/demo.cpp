int main(int argc, char const *argv[])
{
  ifstream file("space.txt");
  string words
  while (file >> word)
  {
    cout << word << endl;
  }
}



#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

struct wordItem {
  string word;
  int count;
};


void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
    ifstream read;
    int i=0;
    string box;
    read.open(ignoreWordFileName);
    if (read.is_open()){
        while(getline(read,box)){
            ignoreWords[i] = box;
            i++;
        }
        read.close();
    }


    else{
        cout << "Failed to open " << ignoreWordFileName << endl;
    }
}




bool isStopWord(string word, string ignoreWords[])
{
   for (int i=0; i< 50; i++){
       if (word == ignoreWords[i]){
           return true;
       }
   }
     return false;

}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
    int count = 0;

    for (int i=0; i< length; i++){
            count += uniqueWords[i].count;
        }

    return count;
}

void arraySort(wordItem uniqueWords[], int length)
{
    for (int i=0; i< length; i++){
        for (int k=i+1; k< length; k++){
            if (uniqueWords[i].count < uniqueWords[k].count){
                string temp;
                int t;

                t = uniqueWords[i].count;
                uniqueWords[i].count = uniqueWords[k].count;
                uniqueWords[k].count = t;

                temp = uniqueWords[i].word;
                uniqueWords[i].word = uniqueWords[k].word;
                uniqueWords[k].word = temp;

            }


        }
    }
}




void printTopN(wordItem uniqueWords[], int topN, int totalNumWords)
{
    for (int i=0; i< topN; i++){
        double prob = (double)uniqueWords[i].count/totalNumWords;
        cout<< setprecision(4) << fixed <<prob << " - " << uniqueWords[i].word << endl;

    }
}

int main(int argc, char*argv[]){

        int timesDoubled=0;
        int uwc=0;
        //cout<< "ARGV[1]: " << argv[1] << endl;

        int increment=0;
        int nsw = 0;
        //creating dynamica array w size 100
         int size = 100;
        wordItem *myArr = new wordItem[size];

    if (argc != 4){
        //cout<< "ARGC: " << argc;
        cout<< "Usage: Assignment2Solution <number of words><inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        exit(0);
    }
    else{


        bool tof = false;
        string sWord[50];
       nsw= getTotalNumberNonStopWords(myArr, 100);


        getStopWords(argv[3], sWord); //storing stop words in an array
        string Box;
        ifstream instream;
        instream.open(argv[2]);
        if (instream.is_open()){
            while(!instream.eof()){


            while(getline(instream, Box, ' ')){
                bool yon = isStopWord(Box, sWord); //check to see if it is a stop word
                if (yon == true){ //if it is, do nothing with the word
                    continue;
                }
                else{
                    //if it isn't a stop word, add it to the array.
                    uwc++; //increment unique word count

                    for (int m=0; m < size; m++){ //size to nsw
                        if (Box == myArr[m].word){
                            myArr[m].count++;
                            tof = true;
                        }
                    }
                    if (tof == false){
                        nsw++;
                        myArr[nsw].count++;
                        myArr[nsw].word = Box;

                        //cout<< "SIZE: "<< size<< endl;
                        //cout << "NSWz: "<< nsw<< endl;


                         if (size-1 == nsw){
                             //cout<< "DOES IT GO HERE"<< endl;

                            timesDoubled += 1;
                            int nsize = 2* size;
                            wordItem *anew = new wordItem[nsize];
                            for (int p =0; p <size; p++){
                                anew[p].word =myArr[p].word;
                                anew[p].count = myArr[p].count;
                            }
                            size = nsize;
                            delete[] myArr;
                            myArr = anew;
                    }



                }
                 increment++;
                        tof = false;

            }

           }
        }

    }

    cout<< "Array doubled: "<< timesDoubled<< endl;
    cout<< "#" << endl;
    cout<< "Unique non-common words: " << nsw<< endl;
    cout<< "#" << endl;
    cout<< "Total non-common words: "<< uwc << endl;
    cout<< "#" << endl;
    cout<< "Probabilities of top " <<argv[1]<<  " most frequent words" << endl;
    cout<< "---------------------------------------" << endl;
    int N = stoi(argv[1]);
     arraySort(myArr, nsw);
    printTopN(myArr, N , increment);
}
}
