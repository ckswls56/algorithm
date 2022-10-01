#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int compare_cnt, move_cnt; //비교 연산횟수, 자료이동 연산횟수 변수

template <typename itemType>
void shellSort(itemType a[], int n)
{
    int i, j, h;
    itemType v;
    h = 1;
    do
    {
        h = 3 * h + 1; // n보다 커질떄까지 h설정
    } while (h < n);
    do
    {
        h = h / 3; // 쉘사이즈 조정
        for (i = h; i <= n; i++)
        {
            v = a[i];
            move_cnt++;
            j = i;
            while (a[j - h] > v)
            {
                compare_cnt++;
                a[j] = a[j - h];
                j -= h;
                move_cnt++;
                if (j <= h - 1)
                {
                    compare_cnt--;
                    break;
                }
            }
            compare_cnt++;
            a[j] = v;
            move_cnt++;
        }
    } while (h > 1);
}

void swap(int &a, int &b)
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
                swap(c[i][0], c[j][0]);
                swap(c[i][1], c[j][1]);
            }
        }
    }
    for (int i = 0; i < n; i++)
        b[i] = c[i][1]; //난수 인덱스를 b배열에 입력

    for (int i = 1; i <= n; i++)
    {
        delete[] c[i];
    }
    delete[] c; //메모리 해제

    int compare_cnt_a, compare_cnt_b, move_cnt_a, move_cnt_b;
    shellSort(a, n - 1); // a정렬
    compare_cnt_a = compare_cnt;
    move_cnt_a = move_cnt;

    compare_cnt = 0;
    move_cnt = 0;

    shellSort(b, n - 1); // b정렬
    compare_cnt_b = compare_cnt;
    move_cnt_b = move_cnt;

    cout << "SortedData_A: ";
    print_arr(a);
    cout << "SortedData_B: ";
    print_arr(b);
    cout << "Compare_Cnt_A " << compare_cnt_a << " DataMove_Cnt_A " << move_cnt_a << endl;
    cout << "Compare_Cnt_B " << compare_cnt_b << " DataMove_Cnt_B " << move_cnt_b << endl;
}