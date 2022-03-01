#include <iostream>
using namespace std;

const int TABLESIZE = 0; // PICK A TABLE SIZE
const int KEYLENGTH = 2;

struct Record
{
	string key;
	// other member data would go here:
};


class Hash
{
private:
	// int KEYLENGTH;
	Record table[TABLESIZE];
	int collisions;

	int hashSum(string key){
/*
	IMPLEMENT THIS
*/
		return -1;
	}


public:
	Hash(){
		collisions = 0;
	}


	//Record search(string key){}

	void insertRecord(Record r){
/*
	IMPLEMENT THIS
*/

	}

	int insertRecordOpenAddress(Record r){
/*
	IMPLEMENT THIS

*/
		return -1;
	}

	void dispHashTable(){
		for(int i = 0; i<TABLESIZE; i++)
			cout << "Entry " << i << " " << table[i].key << endl;
		cout << "number of collisions " << collisions << endl;
		cout << "\n\n";

	}
}; 
////// end of Hash class



string randStr(int l){
	// Gnerate random strings with values A-Z
	// ascii 65-90
	// 0-25+65
	// rand()%26 => 0-25
	// rand()%26+65 => 65

	// utilize the string class constructor:
	// string st(x, ' ') will generate an empty string
	// with x characters 
	string st(l,' ');
	for(int i = 0; i<l; i++)
		st[i] = rand()%26+65;
	
 	return st;
}

int main(){
	// seed the randomizer
	//srand(time(NULL));

	
	// Number of records
	int N = 50; 
	// generate N records


	return 0;
}





