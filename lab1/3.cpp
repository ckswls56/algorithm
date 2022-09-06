#include <iostream>
#include <string>
using namespace std;

template <typename itemType>

class Stack2
{
public:
	Stack2()
	{
		head = new node;
		z = head;
	};
	~Stack2()
	{
		struct node *tmp;
		tmp = z;
		while (tmp != head)
		{
			z = z->next;
			delete tmp;
			tmp = z;
		}
		delete tmp;
	};
	void push(itemType v)
	{
		struct node *next = new node;
		next->key = v;
		next->next = z;
		z = next;
	}
	itemType pop()
	{
		struct node *tmp = z;
		itemType key = z->key;
		z = z->next;
		delete tmp;
		return key;
	}

	int empty()
	{
		if (z == head)
			return 1;
		else
			return 0;
	}

private:
	struct node
	{
		itemType key;
		struct node *next;
	};
	struct node *head, *z;
};

int is_double(string s)
{ // string을 입력받아 double형인지 int형인지 확인한다.
	int flag = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '.')
			flag = 1;
		else if (flag && s[i] != '0')
			return 1;
	}
	return 0;
}

int main()
{
	char c;
	int i;
	double x;
	Stack2<double> acc;

	while ((c = cin.get()) != '\n')
	{
		char s[100];
		x = 0;
		i = 0;
		while (c == ' ')
			cin.get(c);
		if (c == '+') // + 연산
			x = acc.pop() + acc.pop();
		if (c == '*') // * 연산
			x = acc.pop() * acc.pop();
		if (c == '-')
		{ // - 연산
			double a = acc.pop();
			double b = acc.pop();
			x = b - a;
		}
		if (c == '/')
		{ // /연산
			double divisor = acc.pop();
			double dividend = acc.pop();
			x = dividend / divisor;
		}

		while (c >= '0' && c <= '9' || c == '.')
		{
			s[i++] = c;
			cin.get(c);
		}
		if (i) //숫자인경우 atof를 사용하여 double화
		{
			s[i] = 0;
			x = atof(s);
		}

		acc.push(x);
	}

	double res = acc.pop();
	string res_str = to_string(res);
	if (is_double(res_str)) // double인 경우 소수점 둘쨰 자리까지 출력
	{
		cout << fixed;
		cout.precision(2);
	}
	cout << res << '\n';
}