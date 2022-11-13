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

            if (RightSon <= LastNode && a[LeftSon] < a[RightSon])
            {
                Son = RightSon;
            }
            else
                Son = LeftSon;

            if (RootValue < a[Son])
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

bool Direction(struct point p1, struct point p2, struct point p3)
{
    int dxAB, dxAC, dyAB, dyAC, Dir;
    dxAB = p2.x - p1.x;
    dxAC = p3.x - p1.x;
    dyAB = p2.y - p1.y;
    dyAC = p3.y - p1.y;

    if (dxAC * dxAB == 0)
    {
        if (dxAB * dyAC < dyAB * dxAC)
            Dir = 1;
        if (dxAB * dyAC > dyAB * dxAC)
            Dir = -1;
        if (dxAB * dyAC == dyAB * dxAC)
        {
            if (dxAB == 0 && dyAB == 0)
                Dir = 0;
            if ((dxAB * dxAC < 0) || (dyAB * dyAC < 0))
                Dir = -1;
            else if ((dxAB * dxAB + dyAB * dyAB) >=
                     (dxAC * dxAC + dyAC * dyAC))
                Dir = 0;
            else
                Dir = 1;
        }
    }
    else
    {
        if (dyAC / dxAC < dyAB / dxAB)
            Dir = 1;
        if (dyAC / dxAC > dyAB / dxAB)
            Dir = -1;

        if (dyAC / dxAC == dyAB / dxAB)
        {
            if (dxAB == 0 && dyAB == 0)
                Dir = 0;
            if ((dxAB * dxAC < 0) || (dyAB * dyAC < 0))
                Dir = -1;
            else if ((dxAB * dxAB + dyAB * dyAB) >=
                     (dxAC * dxAC + dyAC * dyAC))
                Dir = 0;
            else
                Dir = 1;
        }
    }
    return Dir;
}

bool Intersection(struct line l1, struct line l2)
{
    int LineCrossing;
    if ((Direction(l1.p1, l1.p2, l2.p1) * Direction(l1.p1, l1.p2, l2.p2) <= 0) &&
        (Direction(l2.p1, l2.p2, l1.p1) * Direction(l2.p1, l2.p2, l1.p2) <= 0))
    {
        LineCrossing = true;
    }
    else
    {
        LineCrossing = false;
    }
    return LineCrossing;
}

int IsPointInside(struct point A, struct point P[], int n)
{
    int Count = 0;
    int i;
    int LastPoint = 0;
    int PointOnTestLine = false;
    struct line TestLine;
    struct line PolyLine;
    TestLine.p1 = A;
    TestLine.p2 = A;
    TestLine.p2.x = 10000;
    for (int i = 1; i <= n; i++)
    {
        PolyLine.p1 = PolyLine.p2 = P[i];
        if (i == n)
        {
            PolyLine.p1 = PolyLine.p2 = P[0];
        }
        if (Intersection(TestLine, PolyLine))
            PointOnTestLine = true;
        else
        {
            PolyLine.p2 = P[LastPoint];
            LastPoint = i;
            if (!PointOnTestLine)
            {
                if (Intersection(PolyLine, TestLine))
                {
                    Count++;
                }
            }
            else
            {
                if ((Direction(TestLine.p1, TestLine.p2, PolyLine.p1) *
                         Direction(TestLine.p1, TestLine.p2, PolyLine.p2) <
                     0))
                {
                    Count++;

                    PointOnTestLine = false;
                }
            }
        }
    }
    return ((Count % 2) == 1);
}

int main()
{
    int n, a, b, mini, miny;
    char c;
    struct point A;
    cin >> n >> A.x >> A.y;

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

    MAKE_HEAP mk(n);
    mk.heapsort(angles, n);

    for (int i = 0; i < n; i++)
    {
        cout << polygon[i].c << " ";
    }
    cout << endl;

    if (IsPointInside(A, polygon, n))
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
}

/*
        8 3 5
        A 3 4
        B 1 2
        C 2 5
        D 2 6
        E 9 3
        F 5 3
        G 6 4
        H 8 7
            */