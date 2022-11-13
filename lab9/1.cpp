#include <iostream>
using namespace std;
typedef float itemType;

#define Nmax 100

struct point
{
    char c;
    int x, y;
};
struct point polygon[Nmax];

struct line
{
    struct point p1, p2;
};

int cal, comp;

class MAKE_HEAP
{
private:
    itemType *a;
    int N;

public:
    MAKE_HEAP(int max)
    {
        a = new itemType[max];
        N = 0;
    }
    ~MAKE_HEAP() { delete a; }
    void swap(itemType a[], int i, int j)
    {
        //각도 swap
        itemType temp;
        temp = a[j];
        a[j] = a[i];
        a[i] = temp;
        //도형 swap
        struct point temp2;
        temp2 = polygon[j];
        polygon[j] = polygon[i];
        polygon[i] = temp2;
    }
    void MakeHeap(itemType a[], int Root, int LastNode)
    {
        int Parent, LeftSon, RightSon, Son;
        itemType RootValue;
        Parent = Root;
        RootValue = a[Root];
        struct point RootPoint = polygon[Root];
        LeftSon = 2 * Parent + 1;
        RightSon = LeftSon + 1;
        while (LeftSon <= LastNode)
        {

            if (RightSon <= LastNode && comp++ && a[LeftSon] < a[RightSon])
            {
                Son = RightSon;
            }
            else
                Son = LeftSon;

            if (comp++ && RootValue < a[Son])
            {
                a[Parent] = a[Son];
                polygon[Parent] = polygon[Son];
                Parent = Son;
                LeftSon = Parent * 2 + 1;
                RightSon = LeftSon + 1;
            }
            else
                break;
        }
        a[Parent] = RootValue;
        polygon[Parent] = RootPoint;
    }
    void heapsort(itemType a[], int N)
    {
        int i;
        for (i = N / 2; i >= 0; i--)
            MakeHeap(a, i, N - 1);
        cout << endl;
        for (i = N - 1; i > 0; i--)
        {
            swap(a, 0, i);
            MakeHeap(a, 0, i - 1);
        }
    }
};

float ComputeAngle(struct point p1, struct point p2)
{
    cal++;
    int dx, dy, ax, ay;
    float t;
    dx = p2.x - p1.x;
    ax = abs(dx);
    dy = p2.y - p1.y;
    ay = abs(dy);
    t = (ax + ay == 0) ? 0 : (float)dy / (ax + ay);
    if (dx < 0) // 2,3
        t = 2 - t;
    else if (dy < 0) // 1
        t = 4 + t;
    return t * 90.0;
}

int main()
{
    int n, a, b, mini, miny;
    char c;
    cin >> n;
    n++;

    for (int i = 0; i < n; i++)
    {
        cin >> c >> a >> b;
        polygon[i].c = c;
        polygon[i].x = a;
        polygon[i].y = b;
        if (i == 0 || miny > b)
        {
            mini = i;
            miny = b;
        }
    }

    float *angles = new float[n];

    for (int i = 0; i < n; i++)
    {
        angles[i] = ComputeAngle(polygon[mini], polygon[i]);
    }

    MAKE_HEAP mh(n);
    mh.heapsort(angles, n);

    for (int i = 0; i < n; i++)
    {
        cout << polygon[i].c << " ";
    }
    cout << endl;

    cout << cal << " (수평각 계산 횟수)" << endl;
    cout << comp << " (각의 비교 횟수))";
}
/*
       7
       A 3 4
       B 1 2
       C 2 5
       D 2 6
       E 9 3
       F 5 3
       G 6 4
       H 8 7
           */