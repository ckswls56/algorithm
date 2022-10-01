#include <iostream>
using namespace std;

template <typename itemType>

class Stack1
{
private:
  itemType *stack;
  int p; // top pointer

public:
  Stack1(int max = 100)
  {
    stack = new itemType[max];
    p = 0;
  }
  ~Stack1()
  {
    delete stack;
  }
  inline void push(itemType v)
  {
    stack[p++] = v;
  }
  inline itemType pop()
  {
    return stack[--p];
  }
  inline int empty()
  {
    return !p;
  }
};

int main()
{
  char c;
  Stack1<int> acc(50);
  int x;
  while ((c = cin.get()) != '\n')
  {
    x = 0;
    while (c == ' ') //공백제거
      cin.get(c);
    if (c == '+') //+연산
      x = acc.pop() + acc.pop();
    if (c == '*') //*연산
      x = acc.pop() * acc.pop();
    while (c >= '0' && c <= '9')
    { // atoi
      x = 10 * x + (c - '0');
      cin.get(c);
    }
    acc.push(x);
  }
  cout << acc.pop() << '\n';
}
