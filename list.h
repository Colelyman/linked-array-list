#ifndef LIST_H
#define LIST_H
#include <cstddef>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;
using std::pair;

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
//		cout << "Enter constructor" << endl;
		this->capacity = capacity;
		tail = new Node(capacity);
		head = new Node(capacity);
		Node* first = new Node(capacity);
		first->prev = head;
		first->next = tail;
		head->next = first;
		tail->prev = first;
		list_size = 0;
	//	cout << "Exit constructor" << endl;
		this->capacity = capacity;
	}

	~list() {
		//cout << "Enter destructor" << endl;
		for(Node* n = head; n != tail->prev; n = n->next) {
			if(n == NULL)
				break;
			delete n;
		}
		delete tail;
		//cout << "Exit destructor" << endl;
	}

	void split(Node* n) {
		Node* n2 = new Node(capacity);
		for(int i = capacity / 2, j = 0; i < capacity; i++, j++)
			n2->items[j] = n->items[i];
		n2->size = capacity / 2;
		n->size = capacity / 2;
		n2->next = n->next;
		n->next = n2;
		n2->prev = n;
		if(tail->prev == n)
			tail->prev = n2;
//		if(head->next == n)
//			head->next = n2;
	}

	void move(Node* n, int arrayIndex) {
		for(int i = n->size; i > arrayIndex; i--)
			n->items[i] = n->items[i-1];
	}

	void insert(int index, const ItemType& item) {
		if(index > list_size)
			return;
		pair<Node*, int> npair = find(index);
		Node* n = npair.first;
		int arrayIndex = npair.second;
//		cout << "arrayIndex " << arrayIndex << " n->size " << n->size << endl; 
		if(n->size < capacity) {
			if(arrayIndex < n->size)
				move(n, arrayIndex);
			n->items[arrayIndex] = item;
			n->size++;
			list_size++;
		}
		else if(n->size == capacity) {
			split(n);
			npair = find(index);
			n = npair.first;
			arrayIndex = npair.second;
			if(arrayIndex < n->size)
				move(n, arrayIndex);
//			cout << "arrayIndex " << arrayIndex << " n->size " << n->size << endl; 
			n->items[arrayIndex] = item;
			n->size++;
			list_size++;
		}
	}

	Node* remove(int index) {
		Node* n = find(index);

		return n;
	}

	int calculateIndex(int index, int count, int size) {
		if(index == 0)
			return 0;
		else if(index < capacity)
			return index;
		return (index - (count - size));
	}

	pair<Node*, int> find(int index) {
//		cout << "Enter find()" << endl;
		pair<Node*, int> npair;
		int count;
//		cout << "index: " << index << " list_size: " << list_size << endl;
		if(index <= list_size / 2) {
			count = 0;
			for(Node* n = head->next; n != tail && count <= index; n = n->next) {
				count += n->size;
				npair.first = n;
			}
			npair.second = calculateIndex(index, count, npair.first->prev->size);
			cout << "count: " << count << " index: " << index << " size: " << npair.first->next->size << endl;
//			cout << "if count: " << count << endl;
		}
		else {
			count = list_size;
			for(Node* n = tail->prev; n != head && count >= index; n = n->prev) {
				count -= n->size;
				npair.first = n;
			}
			npair.second = calculateIndex(index, count, npair.first->next->size);
			cout << "count: " << count << " index: " << index << " size: " << npair.first->next->size << endl;
		}
//		cout << "Exit find()" << endl;
		cout << "FINAL, arrayIndex: " << npair.second << endl; 
		return npair;
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
		int count = 0;
		for(Node* n = head->next; n != tail || n == NULL; n = n->next) {
			cout << "node " << count << ": ";
			for(int i = 0; i < n->size; i++) 
				cout << n->items[i] << " ";
			cout << endl;
			count++;
		}
		cout << endl;
	}
};
#endif
