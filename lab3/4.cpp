#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define INF -987654321 // -무한대
long long sum;

template <typename itemType>
int Bubble(int sorted, itemType *a, int n)
{
    int temp;
    if (*(a - 1) > *a)
    {
        sum += (*a) * 2 + *(a - 1);
        temp = *(a);
        *(a) = *(a - 1);
        *(a - 1) = temp;
        sorted = false;
    }
    return sorted;
}

template <typename itemType>
void bubbleSort(itemType a[], int n)
{
    int i, Sorted;
    Sorted = false;
    while (!Sorted)
    {
        Sorted = true;
        for (i = 1; i < n; i++)
        {
            Sorted = Bubble(Sorted, &a[i], n);
        }
    }
}

template <typename itemType>
void shellSort(itemType a[], int n)
{
    int i, j, h;
    itemType v;
    h = 1;
    do
    {
        h = 3 * h + 1;
    } while (h < n);
    do
    {
        h = h / 3;
        for (i = h; i <= n; i++)
        {
            v = a[i];
            sum += v;
            j = i;
            while (a[j - h] > v)
            {
                sum += a[j - h];
                a[j] = a[j - h];
                j -= h;
                if (j <= h - 1)
                    break;
            }
            a[j] = v;
            sum += v;
        }
    } while (h > 1);
}

template <typename itemType>
void insertion(itemType a[], int n)
{
    int i, j;
    itemType v;
    for (i = 2; i <= n; i++)
    {
        v = a[i];
        sum += v;
        j = i;
        while (a[j - 1] > v)
        {
            sum += a[j - 1];
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
        sum += a[j];
    }
}

void swap(int &a, int &b)
{ // a와 b를 서로 교환하는 함수
    int temp = a;
    a = b;
    b = temp;
}

void print_arr(int *arr, int type)
{ //배열을 출력하는 함수
    if (type)
    {
        for (int i = 1; i <= 20; i++)
        {
            cout << arr[i] << " ";
        }
    }
    else
    {
        for (int i = 0; i < 20; i++)
        {
            cout << arr[i] << " ";
        }
    }

    cout << endl;
}

int main()
{
    int n;
    cin >> n;

    int *a = new int[n];
    int *b = new int[n + 1]; //삽입정렬 용도 맨앞원소 - 무한대
    b[0] = INF;
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
                swap(c[i][0], c[j][0]);
                swap(c[i][1], c[j][1]);
            }
        }
    }
    long long sum_bubble, sum_insertion, sum_shell;
    for (int i = 1; i <= n; i++)
        b[i] = c[i - 1][1]; //난수 인덱스를 b배열에 입력
    for (int i = 0; i < n; i++)
    {
        delete[] c[i];
    }
    delete[] c; //메모리 해제

    cout << "UnsortedData_insertion: ";
    print_arr(b, 1);
    sum = 0;
    insertion(b, n); //삽입정렬
    sum_insertion = sum;
    cout << "SortedData_insertion: ";
    print_arr(b, 1);

    for (int i = 0; i < n; i++)
        a[i] = c[i][1]; //난수 인덱스를 b배열에 입력

    cout << "UnsortedData_bubble: ";
    print_arr(a, 0);
    sum = 0;
    bubbleSort(a, n); // 버블정렬
    cout << "SortedData_bubble: ";
    print_arr(a, 0);
    sum_bubble = sum;

    for (int i = 0; i < n; i++)
        a[i] = c[i][1]; //난수 인덱스를 b배열에 입력

    cout << "UnsortedData_shell: ";
    print_arr(a, 0);
    sum = 0;
    shellSort(a, n - 1); // 쉘정렬
    cout << "SortedData_shell: ";
    print_arr(a, 0);
    sum_shell = sum;

    cout << "Insertion Sort: " << sum_insertion << endl;
    cout << "Bubble Sort: \t" << sum_bubble << endl;
    cout << "Shell Sort: \t" << sum_shell << endl;
}