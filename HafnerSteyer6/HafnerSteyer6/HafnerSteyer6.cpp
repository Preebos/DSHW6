// Authors: Evan Hafner, Robin Steyer
// Course Title: Data Structures
// Course Number: CS2028
// Instructor: Anca Ralescu
// TA: Suryadip Chakraborty
// Abstract: Assignment 5: This application tests different collision resolution methods
// in hash tables of various sizes. The user determines the entried and load ratio.
// Preconditions: ?
// Postconditions: ?


#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <vector>

#include <fstream>

using namespace std;


enum collisionResolutionType { LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING };
const int SIZE = 23;

struct node {
	int val;
	node* next;
};


// For getting data
vector<int> arrayOfHashTables[3][16];
vector<node*> chainingHashTable[16];

int totalComparisons[4][16];
int totalInsertions[16];
double averageComparisons[4][16];
int counter;


/*
 *	Add key to the hash table
 *	RETURNS: true if successful, false if failure
 */
bool addToHashTable(vector<int> &hashTable, int value, collisionResolutionType crType) {
	int index = value % hashTable.size();
	counter = 0;

	if (crType == LINEAR_PROBING) {
		if (hashTable[index] == 0) {
			counter++;

			// put value into empty slot
			hashTable[index] = value;
			
			return true;
		}
		else {
			counter++;


			// resolve collision using linear probing
			unsigned count = 0;

			if (hashTable[index] == value) {
				cout << "Number is already in the hash table" << endl;
				return false;
			}



			while (hashTable[index] != 0) {
				counter++;

				index = (index + 1) % hashTable.size();
				count++;

				if (hashTable[index] == value) {
					cout << "Number is already in the hash table" << endl;
					return false;
				}

				if (hashTable[index] == 0) {
					counter++;

					hashTable[index] = value;
					return true;
				}
				else if (count >= hashTable.size()) {
					counter += 2; // 1 addition for each if statement

					// Hash is full
					cout << "Cannot add key; hash table is full" << endl;
					return false;
				}
				counter += 2;
			}
		}
	}



	else if (crType == QUADRATIC_PROBING) {
		if (hashTable[index] == 0) {
			counter++;

			// put value into empty slot
			hashTable[index] = value;
			return true;
		}
		else {
			counter++;

			if (hashTable[index] == value) {
				cout << "Number is already in the hash table" << endl;
				return false;
			}


			// resolve collision using linear probing
			unsigned count = 0;
			int skipFactor = 1;
			while (hashTable[index] != 0) {
				counter++;

				index = (index + skipFactor * skipFactor) % hashTable.size(); // increase by skipFacto^2 each time (1, 4, 9, 16, etc)

				if (hashTable[index] == value) {
					cout << "Number is already in the hash table" << endl;
					return false;
				}

				count++;
				skipFactor++; // double the amount of indices we skip

				if (hashTable[index] == 0) {
					counter++;
					
					hashTable[index] = value;
					return true;
				}
				else if (count >= hashTable.size()) { // Cannot find empty slot
					counter += 2; // Went through 2 comparisons to get here

					cout << "Cannot add key; hash table is full" << endl;
					return false;
				}
				counter += 2;
			}
		}
	}



	else  if (crType == DOUBLE_HASHING) {

		if (hashTable[index] == 0) {
			counter++;

			// put value into empty slot
			hashTable[index] = value;
			return true;
		}
		else {
			counter++;

			if (hashTable[index] == value) {
				cout << "Number is already in the hash table" << endl;
				return false;
			}

			// resolve collision using double hashing
			unsigned count = 0;
			while (hashTable[index] != 0) {
				counter++;

				index = (index + (17 - (value % 17))) % hashTable.size();

				if (hashTable[index] == value) {
					cout << "Number is already in the hash table" << endl;
					return false;
				}

				count++;
				if (hashTable[index] == 0) {
					counter++;

					hashTable[index] = value;
					return true;
				}
				else if (count >= hashTable.size()) {
					counter += 2; // Took two comparisons to get here

					// Hash is full
					return false;
				}
				counter += 2;
			}
		}
		return true;
	}



	return false;
}

/*
 * Adds key to hash table
 * This one uses chaining
 */
bool addToHashTable(vector<node*> &hashTable, int value) {
	counter = 0;

	int index = value % hashTable.size();
	node* newNode = new node;
	newNode->val = value;
	newNode->next = NULL;


	if (hashTable[index] == NULL) {
		counter++;

		hashTable[index] = newNode;
	}
	else {
		counter++;

		node* curNode = hashTable[index];
		if (curNode->val == value) {
			// the value has already been entered
			cout << "Number is already in the hash table" << endl;
			return false;
		}
		while (curNode->next != NULL) {
			counter++;
			if (curNode->val == value) {
				// the value has already been entered
				cout << "Number is already in the hash table" << endl;
				return false;
			}
			curNode = curNode->next;
		}
		counter++;

		curNode->next = newNode;
	}
	return true;
}

int numOfEntries(vector<int> hashTable) {
	int count = 0;
	for (unsigned int n = 0; n < hashTable.size(); n++) {
		if (hashTable[n] != 0) {
			count++;
		}
	}
	return count;
}

int numOfEntries(vector<node*> hashTable) {
	int count = 0;
	node* curNode = NULL;
	for (unsigned int n = 0; n < hashTable.size(); n++) {
		if (hashTable[n] != NULL) {
			curNode = hashTable[n];
			while (curNode != NULL) {
				count++;
				curNode = curNode->next;
			}
		}
	}
	return count;
}

void printHashTable(vector<int> hashTable) {
	cout << "Index: \tEntry: \n";
	for (unsigned int n = 0; n < hashTable.size(); n++) {
		if (hashTable[n] != 0) {
			cout << n << "\t" << hashTable[n] << endl;
		}
		else {
			cout << n << "\t" << "----" << endl;
		}
	}
}

void printHashTable(vector<node*> hashTable) {
	node* curNode = NULL;
	cout << "Index: \tEntries: \n";
	for (unsigned int n = 0; n < hashTable.size(); n++) {
		cout << n;
		if (hashTable[n] != NULL) {
			curNode = hashTable[n];
			while (curNode != NULL) {
				cout << "\t" << curNode->val;
				curNode = curNode->next;
			}
			cout << endl;
		}
		else {
			cout << "\t" << "----" << endl;
		}
	}
}

bool isKeyInHashTable(vector<int> hashTable, int key) 
{
	// Invalid search
	if (key <= 0)
		return false;

	for (unsigned int n = 0; n < hashTable.size(); n++) {
		if (hashTable[n] == key)
			return true;
	}
	return false;
}

bool isKeyInHashTable(vector<node*> hashTable, int key) {
	
	// Invalid Search
	if (key <= 0)
		return false;
	
	node* curNode = NULL;
	for (unsigned int n = 0; n < hashTable.size(); n++) {
		if (hashTable[n] != NULL) {
			curNode = hashTable[n];
			while (curNode != NULL) {
				if (curNode->val == key)
					return true;

				curNode = curNode->next;
			}
		}

	}
	return false;
}






void deleteHashTable(vector<node*> &hashTable) {
	node* curNode = NULL;
	node* nextNode = NULL;
	for (unsigned int n = 0; n < hashTable.size(); n++) {
		if (hashTable[n] != NULL) {
			curNode = hashTable[n];
			while (curNode != NULL) {
				nextNode = curNode->next;
				delete curNode;
				curNode = nextNode;
			}
		}
	}
}

int main() {


	// ------------------------------- PART 1 -----------------------------------
	vector<int> hashTable1;
	vector<int> hashTable2;
	vector<int> hashTable3;
	vector<node*> hashTable4;
	bool hashTableFull = false;
	int value;

	for (int n = 0; n < SIZE; n++) {
		hashTable1.push_back(0);
		hashTable2.push_back(0);
		hashTable3.push_back(0);
		hashTable4.push_back(NULL);
	}

	double loadRatio = 1;
	cout << "This application will insert values into a hash table of size " << SIZE << ".\n\n";
	cout << "What load ratio would you like to use? ";
	cout << "(enter a decimal representation of a percentage, e.g. 0.2 or 0.55)\n";
	cin >> loadRatio;
	while (loadRatio <= 0 || loadRatio >= 1) {
		cout << "Please enter a load ratio value between 0 and 1.\n";
		cin >> loadRatio;
	}

	cout << "Add integers to the hash table by typing them here and then pressing enter after each number: \n";
	while (!hashTableFull) {
		cin >> value;
		addToHashTable(hashTable1, value, LINEAR_PROBING);
		addToHashTable(hashTable2, value, QUADRATIC_PROBING);
		addToHashTable(hashTable3, value, DOUBLE_HASHING);
		addToHashTable(hashTable4, value);
		if ((double)numOfEntries(hashTable1) / (double)SIZE >= loadRatio) {
			hashTableFull = true;
		}
	}
	cout << endl << "Linear Probing:" << endl;
	printHashTable(hashTable1);
	cout << endl <<"Quadratic Probing:" << endl;
	printHashTable(hashTable2);
	cout << endl << "Double Hashing:" << endl;
	printHashTable(hashTable3);
	cout << endl << "Chaining:" << endl;
	printHashTable(hashTable4);
	

	system("pause");

	// ------------------------------- PART 2 -----------------------------------

	srand(time(NULL));
	int tableSize = 1019;

	// Same random numbers so we can accurately test
	vector<int> numberSequence;
	for (int i = 0; i < tableSize; i++) {
		numberSequence.push_back((rand() % 10000) + 1);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < tableSize; k++) {
				arrayOfHashTables[i][j].push_back(NULL);
			}
		}
	}
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < tableSize; j++) {
			chainingHashTable[i].push_back(NULL);
		}
	}

	
	double maxLoadRatio = .1;
	// for each different load ratio
	for (int i = 0; i < 16; i++) {

		for (int j = 0; j < tableSize; j++) {
			addToHashTable(arrayOfHashTables[0][i], numberSequence[j], LINEAR_PROBING);
			totalComparisons[0][i] += counter;


			addToHashTable(arrayOfHashTables[1][i], numberSequence[j], QUADRATIC_PROBING);
			totalComparisons[1][i] += counter;

			
			addToHashTable(arrayOfHashTables[2][i], numberSequence[j], DOUBLE_HASHING);
			totalComparisons[2][i] += counter;


			addToHashTable(chainingHashTable[i], numberSequence[j]); // Crashes here
			totalComparisons[3][i] += counter;

			
			// Break if load ratio is reached
			if ((double)j / (double)tableSize >= maxLoadRatio) {
				totalInsertions[i] = j;
				deleteHashTable(chainingHashTable[i]);//
				arrayOfHashTables[0][i].clear();//
				arrayOfHashTables[1][i].clear();//
				arrayOfHashTables[2][i].clear();//
				chainingHashTable[i].clear();//
				break;
			}
		}

		maxLoadRatio += 0.05;
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 16; j++) {
			averageComparisons[i][j] = totalComparisons[i][j] / (double)totalInsertions[j];
		}
	}

	//ofstream myfile;
	//myfile.open("C:\\Users\\Robin\\Source\\Repos\\DSHW6\\HafnerSteyer6\\Debug\\example.txt");
	
	char* collResTypes[4] = { "linear", "quadratic", "double", "chaining" };
	char* ratios[16] = { ".10",".15",".20",".25",".30",".35",".40",".45",".50",".55",".60",".65",".70",".75",".80",".85" };
	cout << endl << "Ratio\tLinear\tQuad\tDouble\tChaining" << endl;
	//myfile << "Ratio\tLinear\tQuad\tDouble\tChaining\n";
	for (int c = 0; c < 16; c++) {
		cout << ratios[c] << "\t";
		//myfile << ratios[c] << "\t";
		for (int r = 0; r < 4; r++) {
			printf("%0.3f\t", averageComparisons[r][c]);
			//myfile << averageComparisons[r][c] << "\t";
		}
		cout << endl;
		//myfile << "\n";
	}

	//myfile.close();

	system("pause");
	return 0;
}
