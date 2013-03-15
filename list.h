#ifndef LIST_H
#define LIST_H
#include <cstddef>
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

	void split(Node* n) {
		Node* n2 = new Node();
		for(int i = capacity / 2, j = 0; i < capacity; i++, j++)
			n2->items[j] = n->items[i];
	}

	void insert(int index, const ItemType& item) {
		Node* n = find(index);
		if(n == NULL) {
			n = new Node();
			n->items[n->size] = item;
			n->size++;
		}
		else if(n->size < capacity) {
			n->items[n->size] = item;
			n->size++;
		}
		else {
			split(n);
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
		Node* n;

		return n;
	}

	int find(const ItemType& item) {
		int index;

		return index;
	}

	void print() {

	}
};
#endif
