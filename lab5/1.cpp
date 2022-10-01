#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int compare_cnt, move_cnt; //비교 연산횟수, 자료이동 연산횟수 변수

template <typename itemType>
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
        int temp;
        temp = a[j];
        a[j] = a[i];
        a[i] = temp;
    }
    void MakeHeap(itemType a[], int Root, int LastNode)
    {
        int Parent, LeftSon, RightSon, Son;
        itemType RootValue;
        Parent = Root;
        RootValue = a[Root];
        move_cnt++;
        LeftSon = 2 * Parent + 1;
        RightSon = LeftSon + 1;
        while (LeftSon < LastNode)
        {
            compare_cnt++;
            if (RightSon <= LastNode && a[LeftSon] < a[RightSon])
            {
                Son = RightSon;
            }
            else
                Son = LeftSon;
            compare_cnt++;
            if (RootValue < a[Son])
            {
                move_cnt++;
                a[Parent] = a[Son];
                Parent = Son;
                LeftSon = Parent * 2 + 1;
                RightSon = LeftSon + 1;
            }
            else
                break;
        }
        a[Parent] = RootValue;
        move_cnt++;
    }
    void heapsort(itemType a[], int N)
    {
        int i;
        for (i = N / 2; i >= 1; i--)
            MakeHeap(a, i - 1, N - 1);
        for (i = N - 1; i >= 1; i--)
        {
            swap(a, 0, i);
            MakeHeap(a, 0, i - 1);
        }
    }
};

void swap2(int &a, int &b)
{ // a와 b를 서로 교환하는 함수
    int temp = a;
    a = b;
    b = temp;
}
void print_arr(int *arr)
{ //배열을 출력하는 함수
    for (int i = 0; i < 20; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;

    int *a = new int[n];
    int *b = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = n - i; // 내림차순으로 정렬된 배열 생성

    int **c = new int *[n];
    srand((unsigned)time(NULL)); // 현재시간을 이용해 난수발생기 rand()의 초기값을 재설정
    for (int i = 0; i < n; i++)
    {
        c[i] = new int[2];
        c[i][0] = (1 + rand() % n); // 1~n 사이의 숫자 n개를 랜덤하게 생성
        c[i][1] = i + 1;
    } // 난수가 만들어질 때마다 1씩 증가시켜가며 각 난수의 고유 인덱스를 생성

    // bubble sort
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (c[i][0] < c[j][0])
            {
                swap2(c[i][0], c[j][0]);
                swap2(c[i][1], c[j][1]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        b[i] = c[i][1];
    }

    int compare_cnt_a, compare_cnt_b, compare_cnt_c, move_cnt_a, move_cnt_b, move_cnt_c;

    compare_cnt_a = compare_cnt;
    move_cnt_a = move_cnt;

    compare_cnt = 0;
    move_cnt = 0;

    compare_cnt_b = compare_cnt;
    move_cnt_b = move_cnt;

    cout << "SortedData_A: ";

    auto A = MAKE_HEAP<int>(n);
    A.heapsort(a, n);
    move_cnt_a = move_cnt;
    compare_cnt_a = compare_cnt;
    print_arr(a);

    cout << "SortedData_B: ";
    auto B = MAKE_HEAP<int>(n);
    B.heapsort(b, n);
    move_cnt_b = move_cnt;
    compare_cnt_b = compare_cnt;
    print_arr(b);

    for (int i = 0; i < n; i++)
    {
        b[i] = c[i][0];
    }

    cout << "SortedData_C:";
    auto C = MAKE_HEAP<int>(n);
    C.heapsort(b, n);
    move_cnt_c = move_cnt;
    compare_cnt_c = compare_cnt;
    print_arr(b);

    cout << "Compare_Cnt_A " << compare_cnt_a << " DataMove_Cnt_A " << move_cnt_a << endl;
    cout << "Compare_Cnt_B " << compare_cnt_b << " DataMove_Cnt_B " << move_cnt_b << endl;
    cout << "Compare_Cnt_C " << compare_cnt_c << " DataMove_Cnt_C " << move_cnt_c << endl;
}