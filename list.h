#ifndef LIST_H
#define LIST_H
#include <cstddef>
#include <iostream>
#include <utility>
#include <cmath>

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
		this->capacity = capacity;
		tail = new Node(capacity);
		head = new Node(capacity);
		Node* first = new Node(capacity);
		first->prev = head;
		first->next = tail;
		head->next = first;
		tail->prev = first;
		list_size = 0;
	}

	~list() {
		for(Node* n = head; n != tail; n = n->next)
			delete n;
		delete tail;
	}

	void split(Node* n) {
		Node* n2 = new Node(capacity);
		for(int i = capacity / 2, j = 0; i < capacity; i++, j++)
			n2->items[j] = n->items[i];
		n2->size = capacity / 2;
		n->size = capacity / 2;
		n->next->prev = n2; 
		n2->next = n->next;
		n->next = n2;
		n2->prev = n;
		if(tail->prev == n)
			tail->prev = n2;
	}

	void rmove(Node* n, int arrayIndex) {
		for(int i = n->size; i > arrayIndex; i--)
			n->items[i] = n->items[i-1];
	}

	void insert(int index, const ItemType& item) {
		if(index > list_size)
			return;
		pair<Node*, int> npair = find(index);
		Node* n = npair.first;
		int arrayIndex = npair.second;
		if(arrayIndex == n->size && n != tail->prev) {
			n = n->next;
			arrayIndex = 0;
		}
		if(n->size < capacity) {
			if(arrayIndex < n->size)
				rmove(n, arrayIndex);
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
				rmove(n, arrayIndex);
			n->items[arrayIndex] = item;
			n->size++;
			list_size++;
		}
	}

	void lmove(Node* n, int arrayIndex) {
		for(int i = arrayIndex; i < n->size; i++)
			n->items[i] = n->items[i + 1];
	}

	ItemType remove(int index) {
		if(index > list_size)
			return ItemType();
		pair<Node*, int> npair = find(index);
		Node* n = npair.first;
		int arrayIndex = npair.second;
		ItemType item = n->items[arrayIndex];
		if(n->size > 1) {
			lmove(n, arrayIndex);
			n->size--;
		}
		else {
			n->next->prev = n->prev;
			n->prev->next = n->next; 
			delete n;
		}
		list_size--;

		return item;
	}

	pair<Node*, int> find(int index) {
		pair<Node*, int> npair;
		int count;
		if(index <= list_size / 2) {
			count = 0;
			for(Node* n = head->next; n != tail && count <= index; n = n->next) {
				count += n->size;
				npair.first = n;
			}
			count -= npair.first->size;
			npair.second = index - count;
		}
		else {
			count = list_size;
			npair.first = tail->prev;
			for(Node* n = tail->prev; n != head && count >= index; n = n->prev) {
				count -= n->size;
				npair.first = n;
			}
			npair.second = index - count;
		}
	//	cout << "index: " << index << " count: " << count << " arrayIndex: " << npair.second << endl;
		return npair;
	}

	int find(const ItemType& item) {
		int count = 0;
		for(Node* n = head->next; n != tail; n = n->next) {
			for(int i = 0; i < n->size; i++, count++) {
				if(n->items[i] == item)
					return count;
			}
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
	}
};
#endif
