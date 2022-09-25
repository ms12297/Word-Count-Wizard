#include<iostream>
#include<exception>
#include<math.h>
#include<iomanip>
#include<unistd.h>
#include <string>
#include<sstream>

using namespace std;

class Heap
{
private:
	HashNode** array; //the array of pointers to HashNodes
	int capacity;
	int size;

public:
	Heap(int capacity);
	~Heap();
	void insert(HashNode* ptr);
	HashNode* removeMax();
	HashNode* getMax();
	int parent(int k);
	int left(int k);
	int right(int k);
	void siftup(int k);
	void siftdown(int k);
	void print(int k = -1);

private:
	void adjustSize();
};

//==================================================
// Constructor
Heap::Heap(int capacity)
{
	array = new HashNode * [capacity];
	for (int i = 0; i < capacity; i++) { //initalizing with NULL values
		array[i] = NULL;
	}
	size = 0;
	this->capacity = capacity;
}
//Destructor
Heap::~Heap()
{
	//this destructor will always be called after the HashNodes are cleared up by the destructor of HashTable
	//This is why there is no need to clear up space from the individual HashNode* ptrs here
	delete[] array;
}
// Insert an element in Heap keeping the Heap property intact 
void Heap::insert(HashNode* ptr)
{
	if (size == capacity) {
		adjustSize();
	}
	array[size] = ptr;
	siftup(size);
	size++;
}
// Remove the minimum value from Heap keeping the Heap property intact
HashNode* Heap::removeMax()
{
	//swapping root with last element
	HashNode* temp = array[0];
	array[0] = array[size - 1];
	size--;
	siftdown(0);

	return temp;
	//calling sift down function on root
}
// Return (but don't remove) the minimum value from the Heap
HashNode* Heap::getMax()
{
	return array[0];
}
// Returns the index of the parent of the node i
int Heap::parent(int k)
{
	return ((k - 1) / 2);
}
// Returns the index of the left child of the node i
int Heap::left(int k)
{
	return ((2 * k) + 1);
}
// Returns the index of the right child of the node i
int Heap::right(int k)
{
	return ((2 * k) + 2);
}

// Sift-up an element at index k
void Heap::siftup(int k)
{
	if (k != 0) {
		while (array[parent(k)]->value < array[k]->value) {
			//swapping
			HashNode* temp = array[k];
			array[k] = array[parent(k)];
			array[parent(k)] = temp;
			k = parent(k);
			if (k == 0) {
				return;
			}
		}
	}
	else if (k == 0) return;
}

void Heap::siftdown(int k)
{
	if (left(k) > size - 1 && right(k) > size - 1) {
		return;
	}
	else if (left(k) <= size - 1 && right(k) > size - 1) {
		if (array[left(k)]->value > array[k]->value) {
			HashNode* temp = array[k];
			array[k] = array[left(k)];
			array[left(k)] = temp;
			//setting new value for k and recursion
			k = left(k);
			siftdown(k);
		}
		else return;
	}
	else if (left(k) <= size - 1 && right(k) <= size - 1) {
		int s;
		//finding smaller child
		if (array[left(k)]->value > array[right(k)]->value) s = left(k);
		else if (array[left(k)]->value < array[right(k)]->value) s = right(k);
		else s = left(k);
		if (array[s]->value > array[k]->value) {
			HashNode* temp = array[k];
			array[k] = array[s];
			array[s] = temp;
			//setting new value for k and recursion
			k = s;
			siftdown(k);
		}
		else return;
	}
}

//=============================================
void Heap::adjustSize()
{
	HashNode** newArray = new HashNode * [capacity * 2];
	for (int i = 0; i < capacity; i++)
		newArray[i] = array[i];
	delete[] array;
	array = newArray;
	capacity = capacity * 2;
}
//=============================================