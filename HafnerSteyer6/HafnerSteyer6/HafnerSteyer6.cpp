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
#include <ctime>
#include <vector>

using namespace std;

enum collisionResolutionType { LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING };
const int SIZE = 23;

struct node {
	int val;
	node* next;
};

/*	Add key to the hash table
 *	RETURNS: true if successful, false if failure
 */ 
bool addToHashTable(vector<int> &hashTable, int value, collisionResolutionType crType) {
	int index = 0;
	if (crType == LINEAR_PROBING) {
		index = value % SIZE;
		if (hashTable[index] == 0) {
			// put value into empty slot
			hashTable[index] = value;
			return true;
		}
		else {
			// resolve collision using linear probing
			unsigned count = 0;
			while (hashTable[index] != 0) {
				index = (index + 1) % hashTable.size();
				count++;
				if (hashTable[index] == 0) {
					hashTable[index] = value;
					return true;
				}
				else if (count >= hashTable.size()) {
					// Hash is full
					cout << "Cannot add key; hash table is full" << endl;
					return false;
			}
		}
	}
	}
	
	else if (crType == QUADRATIC_PROBING) {
		index = value % SIZE;
		if (hashTable[index] == 0) {
			// put value into empty slot
			hashTable[index] = value;
			return true;
		}
		else {
			// resolve collision using linear probing
			unsigned count = 0;
			int skipFactor = 1;
			while (hashTable[index] != 0) {

				index = (index + skipFactor * skipFactor) % hashTable.size(); // increase by skipFacto^2 each time (1, 4, 9, 16, etc)
				count++;
				skipFactor++; // double the amount of indices we skip

				if (hashTable[index] == 0) {
					hashTable[index] = value;
					return 0;
				}
				else if (count >= hashTable.size()) { // Cannot find empty slot
					cout << "Cannot add key; hash table is full" << endl;
					return false;
				}
			}
		}
	}

	else { // (crType == DOUBLE_HASHING)
		index = value % SIZE;
	}

	return false;
	}

void addToHashTable(vector<node*> &hashTable, int value) {
	int index = value % SIZE;
	node* newNode = new node;
	newNode->val = value;
	newNode->next = NULL;
	if (hashTable[index] == NULL) {
		hashTable[index] = newNode;
}
	else {
		node* curNode = hashTable[index];
		while (curNode->next != NULL) {
			curNode = curNode->next;
		}
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

int main() {
	vector<int> hashTable1;
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

	cout << "Add integers to the hash table by typing them here and then pressing enter after each number: \n";
	while (!hashTableFull) {
		cin >> value;
		addToHashTable(hashTable1, value, QUADRATIC_PROBING);
		if ((double)numOfEntries(hashTable1) / (double)SIZE >= loadRatio) {
			hashTableFull = true;
		}
		/*addToHashTable(hashTable4, value);
		if ((double)numOfEntries(hashTable4) / (double)SIZE >= loadRatio) {
			hashTableFull = true;
		}*/
	}


	printHashTable(hashTable1);

	system("pause");
	return 0;
}
