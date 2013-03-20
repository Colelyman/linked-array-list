#ifndef LIST_H
#define LIST_H
#include <cstddef>
#include <iostream>

using std::cout;
using std::endl;

template <typename ItemType>
class list {
private:
	struct Node {
		Node* prev;
		Node* next;
		ItemType* items;
		int size;

		Node(int capacity) {
			items = new ItemType[capacity];
			prev = NULL;
			next = NULL;
			size = 0;
		}
		Node(int capacity, const ItemType& item) {
			items = new ItemType[capacity];
			items[0] = item;
			prev = NULL;
			next = NULL;
			size = 1;
		}
		~Node() {
			delete[] items;
		}
	};
	int capacity;
	Node* head;
	Node* tail;
	int list_size;
public:
	list(int capacity) {
		cout << "Enter constructor" << endl;
		this->capacity = capacity;
		tail = new Node(capacity);
		head = new Node(capacity);
		head->next = new Node(capacity);
		tail->prev = new Node(capacity);
		head->next->next = tail->prev;
		tail->prev->prev = head->next;
		list_size = 0;
		cout << "Exit constructor" << endl;
	}

	~list() {
		cout << "Enter destructor" << endl;
		for(Node* n = head; n != tail->prev; n = n->next) {
			if(n == NULL)
				break;
			delete n;
		}
		delete tail;
		cout << "Exit destructor" << endl;
	}

	Node* split(Node* n) {
		Node* n2 = new Node();
		for(int i = capacity / 2, j = 0; i < capacity; i++, j++)
			n2->items[j] = n->items[i];
		return n2;
	}

	void insert(int index, const ItemType& item) {
		cout << "Enter insert() " << endl;
		Node* n = find(index);
		if(index > list_size)
			return;
		if(n->size < capacity) {
			n->items[n->size] = item;
			n->size++;
		}
		list_size++;
		cout << "Exit insert()" << endl;
	}

	Node* remove(int index) {
		Node* n = find(index);

		return n;
	}

	Node* find(int index) {
		cout << "Enter find()" << endl;
		Node* n = head;
		if(index <= list_size / 2) {
			for(int i = 0; i <= index; i++)
				n = n->next;
		}
		else {
			n = tail;
			for(int i = list_size; i >= index; i--)
				n = n->prev;
		}
		cout << "Exit find()" << endl;
		return n;
	}

	int find(const ItemType& item) {
		Node* n = head;
		for(int i = 0; i <= list_size; i++) {
			if(item == n)
				return i;
			n->next;
		}

		return -1;
	}

	void print() {
		Node* n = head->next;
		int count = 0;
		if(list_size < capacity) {
			cout << "node " << count << ": ";
			for(int i = 0; i < n->size; i++)
				cout << n->items[i] << " ";
			cout << endl;
			return;
		}
		while(n != tail->prev) {
			cout << "node " << count << ": ";
			for(int i = 0; i < n->size; i++) 
				cout << n->items[i] << " ";
			cout << endl;
			n = n->next;
		}
	}
};
#endif
