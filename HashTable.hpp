#include<iostream>
#include <string>
#include <iomanip>
#include<fstream>
#include<sstream>
#include<math.h>

using namespace std;


class HashTable
{
private:

	DoublyLinkedList<HashNode>* buckets;		// Array of lists of type Hash Nodes
	int size;					    //Unique Word Count in HashTable
	int totalsize; 					//Total number of words in HashTable
	int capacity;				    // Total Capacity of HashTable
	int collisions;					// Total Number of Collisions
	Heap* myMaxHeap;				//MaxHeap to get the word with the highest frequency
	string HashFunction; 			//String to determine which HashFunction to use

public:
	int getTotalsize() {
		return totalsize;
	}

	HashTable(int capacity);
	void select_hashFun(string hashFun);
	unsigned long hashCode(string key);
	void insert(string key);
	int find_freq(string word);
	void erase(string key);
	int get_unique_words();
	int count_collisions();
	int count_words();
	string find_max();
	int max_occ();
	void makeMaxHeap();
	~HashTable();

};

HashTable::HashTable(int capacity)
{
	buckets = new DoublyLinkedList<HashNode>[capacity];	  //Array of a list/chain
	this->capacity = capacity; //HashTable size
	this->size = 0;
	this->collisions = 0;
	this->totalsize = 0;
	this->myMaxHeap = NULL;

}

void HashTable::select_hashFun(string hashFun) {
	//if the user enters valid input
	if (hashFun == "1" || hashFun == "2" || hashFun == "3" || hashFun == "4" || hashFun == "5") {
		this->HashFunction = hashFun;
	}
	else {
		cout << "Invalid input!\nThe Default (Polynomial) Hash Function will be used\n";
		this->HashFunction = "2";
	}
}

unsigned long HashTable::hashCode(string key)
{
	if (this->HashFunction == "1") { //ASCII Sum Hash Function
		unsigned long sum = 0;
		for (int i = 0; i < key.size(); i++) {
			sum += int(key[i]);
		}
		return sum % capacity;
	}

	else if (this->HashFunction == "2") { //Polynomial Hash Function
		unsigned long sum = 0;
		//Horner's rule
		for (int i = key.size() - 1; i >= 0; i--) {
			sum = (sum * 37) + int(key[i]); //char from key is casted to int in every iteration //37
		}
		return sum % capacity;
	}

	else if (this->HashFunction == "3") { //Cyclic Shift Hash Function
		unsigned long sum = 0;
		for (int i = 0; i < key.size(); i++) {
			sum = (sum << 5) | (sum >> 27);
			sum += int(key[i]);
		}
		return sum % capacity;
	}
	else if (this->HashFunction == "4") { //Squaring ASCII Hash Function
		unsigned long sum = 0;
		for (int i = 0; i < key.size(); i++) {
			sum += pow(int(key[i]), 2);
		}
		return sum % capacity;
	}
	else { //XOR Hash Function
		unsigned long sum = 0;
		for (int i = 0; i < key.size(); i++) {
			sum = (sum << 6) ^ (sum >> 26) ^ key[i]; //XOR-ing with key[i] for more even-distribution
		}
		return sum % capacity;
	}
}
//================================================
void HashTable::insert(string key) //inserts a value, or replaces the value of the entry with the key if already there
{

	if (size != capacity) {
		unsigned long x = hashCode(key); //getting the hash code of key
		if (!buckets[x].empty()) {
			for (DoublyLinkedList<HashNode>::iterator q = buckets[x].begin(); q != buckets[x].end(); ++q) {
				if ((*q).key == key) {
					(*q).value += 1; //++ value here because value will be the no. of occurences
					totalsize++; //here, it must be a repetition, not a unique word, so only totalsize increases
					return;
				}
			}
			//if key is not already present then we have a collision
			collisions++;
			//if no matching key found, then pushback entry
			buckets[x].addBack(HashNode(key));
			size++;
			totalsize++;
		}
		else { //if the bucket is empty, pushback
			buckets[x].addBack(HashNode(key));
			size++;
			totalsize++;
		}
	}
	else cout << "Table full!\n";
}
//===================================================
int HashTable::find_freq(string word) //using the quadratic probing principle
{
	unsigned long x = hashCode(word); //getting the hash code of key
	if (!buckets[x].empty()) {
		for (DoublyLinkedList<HashNode>::iterator q = buckets[x].begin(); q != buckets[x].end(); ++q) {
			if ((*q).key == word) {
				return (*q).value;
			}
		}
		//if no matching key found, then not found
		return 0;
	}
	else { //if the bucket is empty, no such key found
		return 0;
	}
}
//=====================================================
// Uncomment it for Task 3
void HashTable::erase(string key)
{
	unsigned long x = hashCode(key); //getting the hash code of key
	if (!buckets[x].empty()) {
		for (DoublyLinkedList<HashNode>::iterator q = buckets[x].begin(); q != buckets[x].end(); ++q) { //PREFIX/POSTFIX ++q instead of q++.
			if ((*q).key == key) {
				totalsize -= (*q).value;
				buckets[x].erase(q);
				size--;
				return;
			}
		}
		//if no matching key found, then error
		cout << "Record not found...!\n";
	}
	else { //if the bucket is empty, no such key found
		cout << "Record not found...!\n";
	}
}
//=====================================================
int HashTable::get_unique_words()
{
	return this->size;
}
//======================================================
int HashTable::count_collisions()
{
	return this->collisions;
}
//======================================================
int HashTable::count_words()
{
	return this->totalsize;
}
//======================================================
HashTable::~HashTable()
{
	//deallocating memory from array of lists
	delete[] buckets;
	//clearing space reserved for myMaxHeap
	if (myMaxHeap != NULL) {
		delete myMaxHeap;
	}

}

void HashTable::makeMaxHeap() {
	myMaxHeap = new Heap(getTotalsize());
	for (int i = 0; i < getTotalsize(); i++) {
		if (!buckets[i].empty()) { //filling up heap with all the values in all buckets
			for (DoublyLinkedList<HashNode>::iterator q = buckets[i].begin(); q != buckets[i].end(); ++q) { //PREFIX/POSTFIX ++q instead of q++.
				myMaxHeap->insert(&(*q));
			}
		}
	}
}
string HashTable::find_max() { //because the sifting has already been done, this function takes O(1) time
	if (myMaxHeap != NULL) {
		return myMaxHeap->getMax()->key;
	}
	else return "Heap is not yet made!\n";
}

int HashTable::max_occ() {
	if (myMaxHeap != NULL) {
		return myMaxHeap->getMax()->value;
	}
	else return 0;
}