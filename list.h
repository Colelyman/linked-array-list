#ifndef LIST_H
#define LIST_H
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

	void insert(int index, const ItemType& item) {

	}

	Node* remove(int index) {
		Node* n = find(index);

		return n;
	}

	Node* find(int index) {
		Node* n;

		return n;
	}

	Node* find(const ItemType& item) {
		Node* n;

		return n;
	}

	void print() {

	}
};
#endif
