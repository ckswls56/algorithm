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

template <typename itemType>
class Queue
{
private:
    itemType *queue;
    int head;
    int tail;
    int size; // 최대크기
public:
    Queue(int max = 100)
    {
        queue = new itemType[max];
        head = 0;
        tail = 0;
        size = max - 1;
    }

    void put(itemType v)
    {
        queue[tail++] = v;
        if (tail > size) // tail이 size 보다 크다면 원형 큐처럼 tail = 0
            tail = 0;
    }
    itemType get()
    {
        itemType t = queue[head++];
        if (head > size)
            head = 0; // head 가 size 보다 크다면 head = 0
        return t;
    }
    int empty()
    {
        return head == tail;
    }
};
Queue<struct treeNode *> queue(50);

void visit(struct treeNode *t)
{
    cout << t->info << " ";
}

void traverse(struct treeNode *t)
{
    queue.put(t);
    while (!queue.empty())
    {
        t = queue.get();
        visit(t); // queue에서 꺼내와 바로 출력
        if (t->l != z)
            queue.put(t->l); //왼쪽 자식이 있다면 queue에 push
        if (t->r != z)
            queue.put(t->r); //오른쪽 자식이 있다면 queue에 push
    }
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
    traverse(stack.pop());
    cout << endl;
    return 0;
}
