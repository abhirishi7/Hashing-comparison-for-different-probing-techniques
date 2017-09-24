/*
 * HashingFunction.cpp
 *
 *  Created on: 23-Sep-2017
 *      Author: Abhishek Tripathi
 * Student ID : 801010002
 *
 */

#include<iostream>
#include<chrono>
#include<iomanip>
#include<time.h>

using namespace std;

#define NIL -1
#define Table_Size 1223  // m value or the hash table size
#define h0(k) (k % Table_Size)  // macro definition for h0(k) used in linear probing
#define h1(k) (1 + (k % (Table_Size - 1)))  // macro definition for h1(k) used in quadratic probing
#define Linear_Probing(k,i) (h0(k) + i) % Table_Size  // macro definition for linear probing
#define Quadratic_Probing(k,i) (h0(k) + (i^2)) % Table_Size  // macro definition for quadratic probing
#define Double_Hashing(k,i) (h0(k) + (i * h1(k))) % Table_Size // macro definition for double hashing

int* hashTable;  // hash table to store keys
int* keyCountstable;  // table to store count of corresponding key
int* keysTable; // table used to store randomly generated keys to be used in different hashing methods.

/*
 *  This class stores all the information gathered after running a particular probing method such as
 *  total probe count, total collisions, total running time of algorithm. This is used in comparing
 *  different hashing methods.
 *
 */
class HashingInfo {
public:
	int runningTime;
	int probeCount;
	int collisionCount;
	int totalKeysInserted;
};

void initializeTables() {
	for (int i = 0; i < Table_Size; i++) {
		hashTable[i] = NIL;
		keyCountstable[i] = 0;
	}
}

void generateRandomKeys(int totalKeys, int smallestKey, int largestKey) {
	for (int i = 0; i < totalKeys; i++)
		keysTable[i] = (rand() % largestKey) + smallestKey;
}

/*
 *  Hashing using linear probing technique
 */
HashingInfo linearProbing(int totalKeys) {

	HashingInfo info;
	int totalCollisions = 0;
	int probeCount = 0;
	int totalKeysInserted = 0;
	initializeTables();
	clock_t start = clock();
	for (int j = 0; j < totalKeys; j++) {
		int key = keysTable[j];
		int i = 0;
		while (i < Table_Size) {
			if (hashTable[Linear_Probing(key, i)] == key) { // check to see if key already present at that index.
				keyCountstable[Linear_Probing(key, i)] += 1; // if yes, just increase the count and return.
				break;
			} else if (hashTable[Linear_Probing(key, i)] == NIL) { // check to see if the space is available.
				hashTable[Linear_Probing(key, i)] = key; // if yes, place the key at that index.
				keyCountstable[Linear_Probing(key, i)] += 1; // also, increase the key count by 1.
				break;
			} else {
				probeCount++;
				i++;
			}
		}
		if (i > 0)
			totalCollisions++;
	}
	for (int i = 0; i < Table_Size; i++) {
		totalKeysInserted += keyCountstable[i];
	}
	clock_t finish = clock();
	info.runningTime = finish - start;
	info.collisionCount = totalCollisions;
	info.probeCount = probeCount;
	info.totalKeysInserted = totalKeysInserted;
	return info;

}

/*
 *  Hashing using quadratic probing technique
 */
HashingInfo quadraticProbing(int totalKeys) {

	HashingInfo info;
	int totalCollisions = 0;
	int probeCount = 0;
	int totalKeysInserted = 0;
	initializeTables();
	clock_t start = clock();
	for (int j = 0; j < totalKeys; j++) {
		int key = keysTable[j];
		int i = 0;
		while (i < Table_Size) {
			if (hashTable[Quadratic_Probing(key, i)] == key) { // check to see if key already present at that index.
				keyCountstable[Quadratic_Probing(key, i)] += 1; // if yes, just increase the count and return.
				break;
			} else if (hashTable[Quadratic_Probing(key, i)] == NIL) { // check to see if the space is available.
				hashTable[Quadratic_Probing(key, i)] = key; // if yes, place the key at that index.
				keyCountstable[Quadratic_Probing(key, i)] += 1; // also, increase the key count by 1.
				break;
			} else {
				probeCount++;
				i++;
			}
		}
		if (i > 0)
			totalCollisions++;
	}
	for (int i = 0; i < Table_Size; i++) {
		totalKeysInserted += keyCountstable[i];
	}
	clock_t finish = clock();
	info.runningTime = finish - start;
	info.collisionCount = totalCollisions;
	info.probeCount = probeCount;
	info.totalKeysInserted = totalKeysInserted;
	return info;

}

/*
 *  Hashing using double hashing technique
 */
HashingInfo doubleHashing(int totalKeys) {

	HashingInfo info;
	int totalCollisions = 0;
	int probeCount = 0;
	int totalKeysInserted = 0;
	initializeTables();
	clock_t start = clock();
	for (int j = 0; j < totalKeys; j++) {
		int key = keysTable[j];
		int i = 0;
		while (i < Table_Size) {
			if (hashTable[Double_Hashing(key, i)] == key) { // check to see if key already present at that index.
				keyCountstable[Double_Hashing(key, i)] += 1; // if yes, just increase the count and return.
				break;
			} else if (hashTable[Double_Hashing(key, i)] == NIL) { // check to see if the space is available.
				hashTable[Double_Hashing(key, i)] = key; // if yes, place the key at that index.
				keyCountstable[Double_Hashing(key, i)] += 1; // also, increase the key count by 1.
				break;
			} else {
				probeCount++;
				i++;
			}
		}
		if (i > 0)
			totalCollisions++;
	}
	for (int i = 0; i < Table_Size; i++) {
		totalKeysInserted += keyCountstable[i];
	}
	clock_t finish = clock();
	info.runningTime = finish - start;
	info.collisionCount = totalCollisions;
	info.probeCount = probeCount;
	info.totalKeysInserted = totalKeysInserted;
	return info;
}

/*
 *  Method to compare different open addressing hashing techniques by comparing total running
 *  time, total probe count, total collisions
 */
void compareHashing(HashingInfo linearInfo, HashingInfo quadInfo,
		HashingInfo doubleInfo) {

	cout << "\t\t\t\t\t" << "--------Case for m = " << Table_Size << "--------"
			<< endl << endl;
	cout << std::right << setw(40) << "Linear probing" << setw(30)
			<< "Quadratic probing" << setw(30) << "Double hashing" << endl
			<< endl;
	cout << std::right << "Total Keys Inserted" << setw(21)
			<< linearInfo.totalKeysInserted << setw(30)
			<< quadInfo.totalKeysInserted << setw(30)
			<< doubleInfo.totalKeysInserted << endl;
	cout << std::right << "Running Time" << setw(22) << linearInfo.runningTime
			<< " msecs" << setw(24) << quadInfo.runningTime << " msecs"
			<< setw(24) << doubleInfo.runningTime << " msecs" << endl;
	cout << std::right << "Probe Count" << setw(29) << linearInfo.probeCount
			<< setw(30) << quadInfo.probeCount << setw(30)
			<< doubleInfo.probeCount << endl;
	cout << std::right << "Initial Collision" << setw(23)
			<< linearInfo.collisionCount << setw(30) << quadInfo.collisionCount
			<< setw(30) << doubleInfo.collisionCount << endl;

}

int main() {

	int smallestKeyValue = 1;
	int largestKeyValue = 10000;
	int totalKeys = 1100;
	hashTable = new int[Table_Size];
	keyCountstable = new int[Table_Size];
	keysTable = new int[totalKeys];

	generateRandomKeys(totalKeys, smallestKeyValue, largestKeyValue);

	HashingInfo linearProbingInfo = linearProbing(totalKeys);
	HashingInfo quadProbingInfo = quadraticProbing(totalKeys);
	HashingInfo doubleHashingInfo = doubleHashing(totalKeys);

	compareHashing(linearProbingInfo, quadProbingInfo, doubleHashingInfo);
	cout << endl << endl << endl;

	return 0;

}

