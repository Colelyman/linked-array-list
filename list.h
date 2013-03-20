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

		Node() {
			prev = NULL;
			next = NULL;
			size = 0;
		}
		Node(const ItemType& item) {
			items[0] = item;
			prev = NULL;
			next = NULL;
			size = 1;
		}
	};
	int capacity;
	Node* head;
	Node* tail;
	int list_size;
public:
	list(int capacity) {
		this->capacity = capacity;
		tail = NULL;
		head = NULL;
		list_size = 0;
	}

	~list() {
		for(Node* n = head; n != tail; n = n->next) 
			delete n;
		delete tail;
	}

	Node* split(Node* n) {
		Node* n2 = new Node();
		for(int i = capacity / 2, j = 0; i < capacity; i++, j++)
			n2->items[j] = n->items[i];
		return n2;
	}

	void insert(int index, const ItemType& item) {
		Node* n = find(index);
		if(index > list_size)
			return;
		if(n == NULL) {
			n = new Node(item);
			head = n;
			tail = n;
			n->size++;
		}
		else if(n->size < capacity) {
			n->items[n->size] = item;
			n->size++;
		}
		else if(n->size == capacity) {
			if(n == tail)
				tail = split(n);
			n->next = split(n);
			n = find(index);
			n->items[n->size] = item;
			n->size++;
		}
		list_size++;
	}

	Node* remove(int index) {
		Node* n = find(index);

		return n;
	}

	Node* find(int index) {
		Node* n = head;
		if(index <= list_size / 2)
			for(int i = 0; i != index; i++)
				n = n->next;
		else {
			n = tail;
			for(int i = list_size; i !=index; i--)
				n = n->prev;
		}

		return n;
	}

	int find(const ItemType& item) {
		Node* n = head;
		for(int i = 0; i < list_size; i++) {
			if(item == n)
				return i;
			n->next;
		}

		return -1;
	}

	void print() {
		Node* n = head->next;
		int count = 0;
		while(n != tail) {
			cout << "node " << count << ": ";
			for(int i = 0; i < n->size; i++) 
				cout << n->items[i] << " ";
			cout << endl;
			n = n->next;
		}
	}
};
#endif
