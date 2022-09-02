#include <iostream>
using  namespace std;

template <typename itemType>

class Stack2
{
public:
	Stack2() {
		head = new  node;
		z = new   node;
		z->head;
	};
	~Stack2() {
		struct node* tmp = new node;
		tmp = z;
		while (tmp!=head) {
			z = z->next;
			delete tmp;
			tmp = z;
		}
	};
	void push(itemType v) {
		struct node* next = new  node;
		next->key = v;
		next->next = z;
		z = next;
	}
	itemType pop() {
		itemType key = z->key;
		z = z->next;
		return key;
	}

	int empty() {
		if (z->data)
			return 1;
		else
			return 0;
	}

private:
	struct node
	{
		itemType key; struct node* next;
	};
	struct node* head, * z;
};

int main()
{
	char c;
	Stack2 <int> acc;

	int x;
	while ((c = cin.get()) != '\n')
	{
		x = 0;
		while (c == ' ') cin.get(c);
		if (c == '+') x = acc.pop() + acc.pop();
		if (c == '*') x = acc.pop() * acc.pop();
		if (c == '-') x = acc.pop() - acc.pop();
		if (c == '/') x = acc.pop() / acc.pop();
		while (c >= '0' && c <= '9')
		{
			x = 10 * x + (c - '0');  cin.get(c);
		}
		acc.push(x);
	}
	cout << acc.pop() << '\n';
}