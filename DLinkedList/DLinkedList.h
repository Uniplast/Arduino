
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <Arduino.h>
//#include <iostream>
//using namespace std;

//Abstract Doubly Linked List
template <typename T>
class DLinkedList  {

public:

	//Default constructor
	DLinkedList();

	//Default destructor
	~DLinkedList();

	//Copy constructor
	DLinkedList(const DLinkedList &list);

	//Check if list is empty
	bool isEmpty() const;

	//Get first element
	const T& first() const;

	//Get last element
	const T& last() const;

	//Get element at index
	const T& getAt(int index) const;

	//Add item to front of list
	void addFront(const T& elem);

	//Add item to end of list
	void addEnd(const T& elem);

	//Remove item at front of list
	void removeFront();

	//Remove item at end of list
	void removeEnd();

	//Print the list
	void printList();

	//Assignment operator overload
	DLinkedList &operator=(const DLinkedList &list);

	//Equality operator overload
	bool operator==(const DLinkedList &list);

private:

	//Node structure
	struct Node {
		//Current element in node
		T element;

		//Pointer to next node in list
		Node *next;

		//Pointer to previous node in list
		Node *prev;
	};

	//List's front sentinel
	Node *head;

	//List's end sentinel
	Node *tail;

protected:

	//Utility add function
	void add(Node *n, const T& elem);

	//Utility remove function
	void remove(Node *n);
};

//Default constructor
template <typename T>
DLinkedList<T>::DLinkedList() {
	head = new Node;
	tail = new Node;

	head->next = tail;
	tail->prev = head;

	head->prev = NULL;
	tail->next = NULL;

	Serial.begin(9600);
}

//Default destructor
template <typename T>
DLinkedList<T>::~DLinkedList() {
	while (!isEmpty()) {
		removeFront();
	}
	delete head;
	delete tail;
}

//Copy constructor
template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList &list) {
	head = new Node;
	tail = new Node;

	head->next = tail;
	tail->prev = head;

	head->prev = NULL;
	tail->next = NULL;

	Node *ptr = list.head->next;

	while (ptr->next != NULL) {
		addEnd(ptr->element);
		ptr = ptr->next;
	}

	Serial.begin(9600);
}

//Check if list is empty
template <typename T>
bool DLinkedList<T>::isEmpty() const {
	return (head->next == tail);
}

//Get element at front of list
template <typename T>
const T& DLinkedList<T>::first() const {
	return head->next->element;
}

//Get element at end of list
template <typename T>
const T& DLinkedList<T>::last() const {
	return tail->prev->element;
}

//Get element at index
template <typename T>
const T& DLinkedList<T>::getAt(int index) const {
	if (!isEmpty()) {
		Node *n = head->next;
		for (int i = 0; i < index; i++) {
			n = n->next;
		}
		if (n->next != NULL) {
			return n->element;
		}
		else {
			Serial.print("DLinkedList: ERROR! Index is out of bounds. Cannot return element at index ");
			Serial.println(index);
		//	cout << "DLinkedList: ERROR! Index is out of bounds. Cannot return element at index " << index << endl;
			return false;
		}
	}
	else {
		Serial.println("DLinkedList: ERROR! Cannot return element from an empty list.");
		//cout << "DLinkedList: ERROR! Cannot return element from an empty list." << endl;
		return false;
	}
}

//Utility add function
template <typename T>
void DLinkedList<T>::add(Node *n, const T& elem) {
	Node *newNode = new Node;
	newNode->element = elem;
	
	newNode->next = n;
	newNode->prev = n->prev;
	n->prev->next = newNode;
	n->prev = newNode;
}

//Add to front of list
template <typename T>
void DLinkedList<T>::addFront(const T& elem) {
	add(head->next, elem);
}

//Add to end of list
template <typename T>
void DLinkedList<T>::addEnd(const T& elem) {
	add(tail, elem);
}

//Utility remove function
template <typename T>
void DLinkedList<T>::remove(Node *n) {
	if (!isEmpty()) {
		n->prev->next = n->next;
		n->next->prev = n->prev;

		delete n;
	}
}

//Remove element from front of the list
template <typename T>
void DLinkedList<T>::removeFront() {
	remove(head->next);
}

//Remove element from end of the list
template <typename T>
void DLinkedList<T>::removeEnd() {
	remove(tail->prev);
}

//Print the list
template <typename T>
void DLinkedList<T>::printList() {
	Node *n = head->next;
	while (n->next != NULL) {
		Serial.print(n->element);
		//cout << n->element << " ";
		n = n->next;
	}
}

//Assignment operator
template <typename T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &list) {
	if (!isEmpty()) {
		const Node *node = head->next;
		while (node->next != NULL) {
			removeFront();
			node = head->next;
		}
	}
	const Node *node = list.head->next;

	while (node->next != NULL) {
		addEnd(node->element);
		node = node->next;
	}
	return *this;
}

//Equality operator
//Checks for equality, order, and number of all elements
template <typename T>
bool DLinkedList<T>::operator==(const DLinkedList<T> &list) {
	const Node *leftNode = head->next;
	const Node *rightNode = list.head->next;

	while (leftNode->next != NULL && rightNode->next != NULL) {
		if (leftNode->element != rightNode->element) {
			return false;
		}
		leftNode = leftNode->next;
		rightNode = rightNode->next;
	}
	if ((leftNode->next != tail && rightNode->next == list.tail) || (leftNode->next == tail && rightNode->next != list.tail)) {
		return false;
	}
	return true;
}
#endif
