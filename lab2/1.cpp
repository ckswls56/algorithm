#include <iostream>
using namespace std;

struct treeNode
{
    char info; // key값
    struct treeNode *l, *r;
};

struct treeNode *x, *z; // x = 입력받는 용도 z = leaf임을 표현하는 용도

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
        stack[p++] = v; // v를 입력받고 top pointer 증가
    }
    inline itemType pop()
    {
        return stack[--p]; // top pointer를 뺴고 stack값을 retrun
    }
    inline int empty()
    {
        if (p == 0)
            return 1;
        else
            return 0;
    }
};

void visit(struct treeNode *t)
{
    cout << t->info << " "; // key값 출력
}
void traverse(struct treeNode *t)
{
    if (t != z) // leaf가 아니라면 중위순회
    {
        traverse(t->l);
        visit(t);
        traverse(t->r);
    }
}

int main()
{
    char c;
    Stack<struct treeNode *> stack(50); // node를 저장할 stack생성
    z = new treeNode;
    z->l = z;
    z->r = z;
    while ((c = cin.get()) != '\n')
    {
        while (c == ' ') // 공백제거
            cin.get(c);
        x = new treeNode;
        x->info = c; // key값 입력
        x->l = z;    // left자식 z
        x->r = z;    // right자식 z
        if (c == '+' || c == '*' || c == '-')
        {
            if (!stack.empty()) // stack이 비어있지 않다면 꺼내와서 오른쪽 자식에 연결
                x->r = stack.pop();
            if (!stack.empty()) // stack이 비어있지 않다면 꺼내와서 왼쪽 자식에 연결
                x->l = stack.pop();
        }
        stack.push(x); //노드 push
    }
    traverse(stack.pop()); // root 노드 중위순회 시작
    cout << endl;
    return 0;
}
