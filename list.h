#ifndef LIST_H
#define LIST_H
template<typename type>
class list {
public:
	list(int capacity);
	void insert(int index, const type& item);
	Node* remove(int index);
	Node* find(type item);
	void print();
private:
	int capacity;
	struct Node {
		Node* prev;
		Node* next;
		type items[capacity];
		int size;
	};
	Node* head, tail;
	int list_size;
};
#endif
