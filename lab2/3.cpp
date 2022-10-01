#include <iostream>
using namespace std;

struct treeNode
{
    char info;
    struct treeNode *l, *r;
};

struct treeNode *x, *z;

template <typename itemType>
class Stack
{
private:
    itemType *stack;
    int p;

public:
    Stack(int max = 100)
    {
        stack = new itemType[max];
        p = 0;
    }
    ~Stack()
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
        if (p == 0)
            return 1;
        else
            return 0;
    }
};

int traverse(struct treeNode *t, int level, char find)
{
    if (t != z)
    {
        if (t->info == find)
        {
            return level; // 찾은경우 level 반환
        }
        int res;
        res = traverse(t->l, level + 1, find); // 왼쪽 자식으로 들어가 탐색 level+1
        if (res != -1)
            return res;                        //만약 찾은 경우 반환
        res = traverse(t->r, level + 1, find); // 오른쪽 자식으로 들어가 탐색 level+1
        return res;
    }
    else
        return -1;
}

int main()
{
    char c;
    Stack<struct treeNode *> stack(50);
    z = new treeNode;
    z->l = z;
    z->r = z;
    while ((c = cin.get()) != '\n')
    {
        while (c == ' ')
            cin.get(c);
        x = new treeNode;
        x->info = c;
        x->l = z;
        x->r = z;
        if (c == '+' || c == '*' || c == '-')
        {
            if (!stack.empty())
                x->r = stack.pop();
            if (!stack.empty())
                x->l = stack.pop();
        }
        stack.push(x);
    }
    char find;
    cin >> find;                              //찾을 문자 입력
    int res = traverse(stack.pop(), 1, find); // 문자 찾기

    if (res == -1) // 못찾은경우
        cout << "Not Found";
    else
        cout << res;
    cout << endl;
    return 0;
}
