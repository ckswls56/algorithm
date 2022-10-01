#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define INF -987654321 // -무한대

int compare_cnt, move_cnt; //비교 연산횟수, 자료이동 연산횟수 변수

template <typename itemType>
void insertion(itemType a[], int n)
{
    int i, j;
    itemType v;
    for (i = 2; i <= n; i++)
    {
        v = a[i];
        move_cnt++;
        j = i;
        while (a[j - 1] > v)
        {
            compare_cnt++;
            a[j] = a[j - 1];
            move_cnt++;
            j--;
        }
        compare_cnt++;
        a[j] = v;
        move_cnt++;
    }
}

void swap(int &a, int &b)
{ // a와 b를 서로 교환하는 함수
    int temp = a;
    a = b;
    b = temp;
}

void print_arr(int *arr, int n)
{ //배열을 출력하는 함수
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;

    int *a = new int[n + 1];
    int *b = new int[n + 1];
    a[0] = INF; // 첫번쨰 원소를 -무한대
    b[0] = INF; // 첫번쨰 원소를 -무한대
    for (int i = 1; i <= n; i++)
        a[i] = n - (i - 1); // 내림차순으로 정렬된 배열 생성

    int **c = new int *[n + 1];
    srand((unsigned)time(NULL)); // 현재시간을 이용해 난수발생기 rand()의 초기값을 재설정
    for (int i = 1; i <= n; i++)
    {
        c[i] = new int[2];
        c[i][0] = (1 + rand() % n); // 1~n 사이의 숫자 n개를 랜덤하게 생성
        c[i][1] = i;
    } // 난수가 만들어질 때마다 1씩 증가시켜가며 각 난수의 고유 인덱스를 생성

    // bubble sort
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (c[i][0] < c[j][0])
            {
                swap(c[i][0], c[j][0]);
                swap(c[i][1], c[j][1]);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        b[i] = c[i][1]; //난수 인덱스를 b배열에 입력

    for (int i = 0; i < n; i++)
        delete[] c[i];
    delete[] c;

    int compare_cnt_a, compare_cnt_b, move_cnt_a, move_cnt_b;
    insertion(a, n); // a정렬
    compare_cnt_a = compare_cnt;
    move_cnt_a = move_cnt;

    compare_cnt = 0;
    move_cnt = 0;

    insertion(b, n); // b정렬
    compare_cnt_b = compare_cnt;
    move_cnt_b = move_cnt;

    cout << "SortedData_A: ";
    print_arr(a, n);
    cout << "SortedData_B: ";
    print_arr(b, n);
    cout << "Compare_Cnt_A " << compare_cnt_a << " DataMove_Cnt_A " << move_cnt_a << endl;
    cout << "Compare_Cnt_B " << compare_cnt_b << " DataMove_Cnt_B " << move_cnt_b << endl;
}