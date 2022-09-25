#include<iostream>
#include <string>
#include <iomanip>
#include<fstream>
#include<sstream>
#include<math.h>

using namespace std;

class HashNode
{
private:
	string key; //the word
	int value; //no. of occurences of the word
public:
	HashNode() { //default constructor
		key = "EMPTY";
		value = 0;
	}
	HashNode(string key)
	{
		this->key = key;
		this->value = 1;
	}
	friend class HashTable;
	friend class Heap;
};
