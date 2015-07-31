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

using namespace std;


enum collisionResolutionType { LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING };
const int SIZE = 1009;

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
	int index = value % SIZE;
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
			while (hashTable[index] != 0) {
				counter++;

				index = (index + 1) % hashTable.size();
				count++;
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

			// resolve collision using linear probing
			unsigned count = 0;
			int skipFactor = 1;
			while (hashTable[index] != 0) {
				counter++;

				index = (index + skipFactor * skipFactor) % hashTable.size(); // increase by skipFacto^2 each time (1, 4, 9, 16, etc)
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

			// resolve collision using double hashing
			unsigned count = 0;
			while (hashTable[index] != 0) {
				counter++;

				index = (index + (17 - (value % 17))) % hashTable.size();
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
 * Adds key to hash table, this one uses chaining
 * 
 */
void addToHashTable(vector<node*> &hashTable, int value) {
	counter = 0;

	int index = value % SIZE;
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
		while (curNode->next != NULL) {
			counter++;
			curNode = curNode->next;
		}
		counter++;

		curNode->next = newNode;
	}
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
			cout << endl;
		}
	}
}

int main() {
	/*vector<int> hashTable1;
	vector<int> hashTable2;
	vector<int> hashTable3;
	vector<node*> hashTable4;
	bool hashTableFull = false;
	int value;

	for (int n = 0; n < SIZE; n++) {
		hashTable1.push_back(NULL);
		hashTable2.push_back(NULL);
		hashTable3.push_back(NULL);
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

	/*cout << "Add integers to the hash table by typing them here and then pressing enter after each number: \n";
	while (!hashTableFull) {
		cin >> value;
		addToHashTable(hashTable1, value, DOUBLE_HASHING);
		if ((double)numOfEntries(hashTable1) / (double)SIZE >= loadRatio) {
			hashTableFull = true;
		}
	}
	*/



	// PART 2
	srand(time(NULL));

	// Same random numbers so we can accurately test
	vector<int> numberSequence;
	for (int i = 0; i < SIZE; i++) {
		numberSequence.push_back((rand() % 10000) + 1);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < SIZE; k++) {
				arrayOfHashTables[i][j].push_back(NULL);
			}
		}
	}
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < SIZE; j++) {
			chainingHashTable[i].push_back(NULL);
		}
	}

	
	double maxLoadRatio = .1;
	// for each different load ratio
	for (int i = 0; i < 16; i++) {

		for (int j = 0; j < SIZE; j++) {
			addToHashTable(arrayOfHashTables[0][i], numberSequence[j], LINEAR_PROBING);
			totalComparisons[0][j] = counter;


			addToHashTable(arrayOfHashTables[1][i], numberSequence[j], QUADRATIC_PROBING);
			totalComparisons[1][j] = counter;

			
			addToHashTable(arrayOfHashTables[2][i], numberSequence[j], DOUBLE_HASHING);
			totalComparisons[2][j] = counter;


			addToHashTable(chainingHashTable[i], numberSequence[j]);
			totalComparisons[3][j] = counter;

			//cout << j << endl;
			
			// Break if load ratio is reached
			if ((double)j / (double)SIZE >= maxLoadRatio) {
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

	char* collResTypes[4] = { "linear", "quadratic", "double", "chaining" };
	cout << "load ratio:\t.10\t.15\t.20\t.25\t.30\t.35\t.40\t.45\t.50\t.55\t.60\t.65\t.70\t.75\t.80\t.85" << endl;
	for (int r = 0; r < 4; r++) {
		cout << collResTypes[r] << "\t";
		for (int c = 0; c < 16; c++) {
			printf("%0.4f\t", averageComparisons[r][c]);
		}
		cout << endl << endl;
	}

	
	
	







	//printHashTable(hashTable1);

	system("pause");
	return 0;
}
