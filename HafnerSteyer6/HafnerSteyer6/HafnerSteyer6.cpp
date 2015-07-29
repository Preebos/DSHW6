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

enum collisionResolutionType {LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING, CHAINING};
const int SIZE = 23;

void addToHashTable(vector<int> &hashTable, int value, collisionResolutionType crType) {
	int index = 0;
	if (crType == LINEAR_PROBING) {
		index = value % SIZE;
		hashTable[index] = value;
	}
	
	else if (crType == QUADRATIC_PROBING) {

	}

	else if (crType == DOUBLE_HASHING) {

	}

	else {

	}

	return;
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

int main() {
	vector<int> hashTable1;
	vector<int> hashTable2;
	vector<int> hashTable3;
	vector<int> hashTable4;
	bool hashTableFull = false;
	int value;

	for (int n = 0; n < SIZE; n++) {
		hashTable1.push_back(0);
	}

	double loadRatio = 0;
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
		if ((double)numOfEntries(hashTable1) / (double)SIZE >= loadRatio) {
			hashTableFull = true;
		}
	}

	printHashTable(hashTable1);

	system("pause");
	return 0;
}
