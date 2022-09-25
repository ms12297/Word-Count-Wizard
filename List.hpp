#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<exception>

using namespace std;

template <typename T>
class Node
{
private:
	T elem; //data element (type string in this case)
	Node<T>* next; //Link (pointer) to the next Node
	Node<T>* prev; //Link (pointer) to the previous Node
	template <typename U>
	friend class DoublyLinkedList;

public:
	Node() : next(NULL), prev(NULL)
	{}
	Node(T elem) : elem(elem), next(NULL), prev(NULL)
	{}
};
//==============================================================
template <typename T>
class DoublyLinkedList
{
private:
	Node<T>* head; 	// pointer to the head of List
	Node<T>* tail; 	// pointer to the tail of List
public:
	class iterator {
	public:
		iterator(Node<T>* u) {
			v = u;
		}
		//traits
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;

		T& operator* () {
			return v->elem;
		}

		bool operator==(const iterator& p) const {
			return v == p.v;
		}

		bool operator!=(const iterator& p) const {
			return v != p.v;
		}

		iterator& operator++() {
			v = v->next;
			return *this;
		}

		iterator& operator--() {
			v = v->prev;
			return *this;
		}


	private:
		Node<T>* v; // pointer to the node
		template <typename U> friend class DoublyLinkedList;
	};

	DoublyLinkedList(); // empty list constructor
	~DoublyLinkedList(); // destructor to clean up all nodes
	bool empty() const; // is list empty?
	const T& front() const; // get the value (element) from front Node of list
	const T& back() const;  // get the value (element) from last Node of the List 
	void addBefore(Node<T>* ptr, const T& elem);	 //add a new node before ptr
	void addFront(const T& elem); // add a new node to the front of list
	void addBack(const T& elem); //add a new node to the back of the list
	void removeFront(); // remove front node from list
	void removeBack();  // remove last node from list
	void erase(iterator q);
	void display() const;	// display all element of the list

	iterator begin() const {
		return iterator(head->next);
	}
	iterator end() const {
		return iterator(tail);
	}
};
//===================================


//FUNCTION DEFINITIONS
template <typename T>
void DoublyLinkedList<T>::erase(iterator q) {

	if (!empty()) {
		Node<T>* ptr = q.v;
		Node<T>* forw = ptr->next;
		Node<T>* back = ptr->prev;
		forw->prev = back;
		back->next = forw;
		delete ptr;
	}
	else
		cout << "List is empty!\n";
}

//============================================================
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	head = new Node<T>;
	tail = new Node<T>;
	head->next = tail;
	tail->prev = head;
}
//============================================================
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() // destructor to clean up all nodes
{
	while (!empty()) {
		removeFront();
	}
	delete head;
	delete tail;
}
//============================================================
template <typename T>
bool DoublyLinkedList<T>::empty() const // is list empty?
{
	if (head->next == tail)
		return true;
	else
		return false;
}
//============================================================
template <typename T>
const T& DoublyLinkedList<T>::front() const // get front element
{

	if (empty())
		cout << "List is empty!\n";
	else
		return head->next->elem;
}
//============================================================
template <typename T>
const T& DoublyLinkedList<T>::back() const // get front element
{
	//CHECK!
	if (empty())
		cout << "List is empty!\n";
	else
		return tail->prev->elem;
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addBefore(Node<T>* ptr, const T& elem)
{
	Node<T>* v = new Node<T>(elem);
	v->next = ptr;
	v->prev = ptr->prev;
	ptr->prev->next = v;
	ptr->prev = v;
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addFront(const T& elem) // add to front of list
{
	Node<T>* v = new Node<T>(elem);
	v->next = head->next;
	v->prev = head;
	head->next->prev = v;
	head->next = v;
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addBack(const T& elem) // add to Back of the list
{
	Node<T>* v = new Node<T>(elem);
	v->next = tail;
	v->prev = tail->prev;
	tail->prev->next = v;
	tail->prev = v;
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::removeFront() // remove front item from list
{
	if (!empty()) {
		Node<T>* old = head->next;
		head->next = old->next;
		old->next->prev = head;
		delete old;
	}
	else
		cout << "List is empty!\n";
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::removeBack() // remove last item from list
{
	if (!empty()) {
		Node<T>* old = tail->prev;
		tail->prev = old->prev;
		old->prev->next = tail;
		delete old;
	}
	else
		cout << "List is empty!\n";
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::display() const
{
	Node<T>* curr = head;
	while (curr != NULL)
	{
		cout << "+------";
		curr = curr->next;
	}
	cout << "+" << endl << "|";
	curr = head;
	while (curr != NULL)
	{
		if (curr == head)		cout << " Head |";
		else if (curr == tail)	cout << " Tail |";
		else 					cout << setw(5) << curr->elem << " |";

		curr = curr->next;
	}
	curr = head;
	cout << endl;
	while (curr != NULL)
	{
		cout << "+------";
		curr = curr->next;
	}
	cout << "+" << endl;
}
//============================================================


