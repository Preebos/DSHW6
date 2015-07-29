// Authors: Evan Hafner, Robin Steyer
// Course Title: Data Structures
// Course Number: CS2028
// Instructor: Anca Ralescu
// TA: Suryadip Chakraborty
// Abstract: Assignment 4: This application serves to display the effectiveness of
//	various sorting algorithms. Run the program for a better description.
// Preconditions: ?
// Postconditions: ?

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum collisionResolutionType {LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING, CHAINING};

void addToHashTable(int hashTable[], int value, collisionResolutionType crType) {
	if (crType == LINEAR_PROBING) {

	}
	
	else if (crType == QUADRATIC_PROBING) {

	}

	else if (crType == DOUBLE_HASHING) {

	}

	else {

	}

	return;
}

int main() {
	const int size = 23;
	int hashTable1[size];
	int hashTable2[size];
	int hashTable3[size];
	int hashTable4[size];
	bool hashTableFull = false;
	int value;

	double loadRatio = 0;
	cout << "This application will insert values into a hash table of size " << size << ".\n\n";
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
	}

	system("pause");
	return 0;
}
