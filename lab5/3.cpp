#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef int itemType;

int compare_cnt, move_cnt; //비교 연산횟수, 자료이동 연산횟수 변수

typedef struct node *node_pointer; 
typedef struct node {
      itemType value; 
      node_pointer next;
};

node_pointer TABLE[10], x, z, temp;


void radixSort(itemType *a, int n) {
      int i,j, cnt, radix, radix_mod =10, cipher=0; 
      i=n; 
      while(i>0) { i=i/10; cipher++; } // ascipher : 입력 데이터의 자리수 (ex. 450 -> 3)
      for(i=0; i<cipher; i++) {
            for(j=0; j<n; j++) {
                  cnt=0; radix = (a[j]%radix_mod)/(radix_mod/10); 
                          /* radix_mod = 10 이면 radix는 a[j]의 일의 자리수
                         radix_mod = 100 이면 radix는 a[j]의 십의 자리수 */
                  temp = new node; temp->value = a[j]; temp->next = z; 
                  if(TABLE[radix] == z) {  
                          // z는 list의 끝을 확인하기 위한 노드 포인터 (NULL에 해당)
                        TABLE[radix]=temp; 
                  } else {
                        x=TABLE[radix]; 
                        while(x->next != z) {
                              x=x->next; 
                        }
                        x->next=temp; 
                  }
            }

            for(j=0; j<10; j++) {
                  if(TABLE[j]!=z) {
                        x=TABLE[j]; 
                        while(x!=z) {
                              a[cnt++] = x->value; 
                              temp = x; // 메모리에서 노드를 삭제하기 위해 임시 저장
                              x=x->next; 
                                             delete temp; // 배열에 이미 넣은 노드를 메모리에서 삭제
                        }
                  }
                  TABLE[j]=z; 
            }
            radix_mod*=10; 
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
        b[i] = c[i][1]; // 난수
    }

    int compare_cnt_a, compare_cnt_b, compare_cnt_c, move_cnt_a, move_cnt_b, move_cnt_c;

    compare_cnt_a = compare_cnt;
    move_cnt_a = move_cnt;

    compare_cnt = 0;
    move_cnt = 0;

    compare_cnt_b = compare_cnt;
    move_cnt_b = move_cnt;

    cout << "SortedData_A: ";

    radixSort(a,n);
    move_cnt_a = move_cnt;
    compare_cnt_a = compare_cnt;
    print_arr(a);

    cout << "SortedData_B: ";
    radixSort(b,n);
    move_cnt_b = move_cnt;
    compare_cnt_b = compare_cnt;
    print_arr(b);

    for (int i = 0; i < n; i++)
    {
        b[i] = c[i][0]; //중복이 허용된 난수
    }

    cout << "SortedData_C:";
    radixSort(b,n);
    move_cnt_c = move_cnt;
    compare_cnt_c = compare_cnt;
    print_arr(b);

    cout << "Compare_Cnt_A " << compare_cnt_a << " DataMove_Cnt_A " << move_cnt_a << endl;
    cout << "Compare_Cnt_B " << compare_cnt_b << " DataMove_Cnt_B " << move_cnt_b << endl;
    cout << "Compare_Cnt_C " << compare_cnt_c << " DataMove_Cnt_C " << move_cnt_c << endl;
}