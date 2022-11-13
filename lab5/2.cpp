#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int compare_cnt, move_cnt; //비교 연산횟수, 자료이동 연산횟수 변수


template <typename itemType>
void CountSort(itemType *a, itemType *b, itemType *N, int n, int k) {
      int i,j; 
      for(i=1; i<=k; i++) N[i]=0; 
      for(i=1; i<=n; i++) N[a[i]] = N[a[i]] + 1;
      for(i=2; i<=k; i++) N[i] = N[i] + N[i-1]; 
      for(j=n; j>=1; j--) { 
             b[N[a[j]]] = a[j]; 
             move_cnt++;
             N[a[j]] = N[a[j]] - 1; 
       } 
}



void swap2(int &a, int &b)
{ // a와 b를 서로 교환하는 함수
    int temp = a;
    a = b;
    b = temp;
}
void print_arr(int *arr)
{ //배열을 출력하는 함수
    for (int i = 1; i <= 20; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    
    cin >> n;
    int k = n; // k 설정
    int *a = new int[n+1];
    int *b = new int[n+1];
    int *N= new int[k+1];
    for (int i = 1; i <= n; i++)
        a[i] = n - i+1; // 내림차순으로 정렬된 배열 생성

    int **c = new int *[n+1];
    srand((unsigned)time(NULL)); // 현재시간을 이용해 난수발생기 rand()의 초기값을 재설정
    for (int i = 1; i <= n; i++)
    {
        c[i] = new int[2];
        c[i][0] = (rand() % 10 + 1 ); // 1~n사이의 숫자 n개를 랜덤하게 생성
        c[i][1] = i;
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

    int compare_cnt_a, compare_cnt_b, compare_cnt_c, move_cnt_a, move_cnt_b, move_cnt_c;

    compare_cnt_a = compare_cnt;
    move_cnt_a = move_cnt;

    compare_cnt = 0;
    move_cnt = 0;

    compare_cnt_b = compare_cnt;
    move_cnt_b = move_cnt;

    cout << "SortedData_A: ";
    CountSort(a,b,N,n,k);
    move_cnt_a = move_cnt;
    compare_cnt_a = compare_cnt;
    print_arr(b);

    for (int i = 1; i <= n; i++)
    {
        a[i] = c[i][1]; //난수
    }
    cout << "SortedData_B: ";
    CountSort(a,b,N,n,k);


    move_cnt_b = move_cnt;
    compare_cnt_b = compare_cnt;
    print_arr(b);

    for (int i = 1; i <= n; i++)
    {
        a[i] = c[i][0]; //중복이 허용된 난수
    }

    cout << "SortedData_C:";
    CountSort(a,b,N,n,k);
    move_cnt_c = move_cnt;
    compare_cnt_c = compare_cnt;
    print_arr(b);

    cout << "Compare_Cnt_A " << compare_cnt_a << " DataMove_Cnt_A " << move_cnt_a << endl;
    cout << "Compare_Cnt_B " << compare_cnt_b << " DataMove_Cnt_B " << move_cnt_b << endl;
    cout << "Compare_Cnt_C " << compare_cnt_c << " DataMove_Cnt_C " << move_cnt_c << endl;
}