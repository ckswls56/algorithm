#include <iostream>
#include <cstring>
using namespace std;
int *SP; // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
const int q = 33554393;
const int d = 26;
void brutesearch(char *p, char *a)
{ // p : Pattern String, a : Text String
    int comp, idx1, idx2;
    comp = 0;
    idx1 = 0;
    idx2 = 0;
    int i, j, m = strlen(p), n = strlen(a);
    for (i = 0; i <= n - m; i++)
    {
        for (j = 0; j < m; j++)
        {
            comp++;
            if (a[i + j] != p[j])
                break;
        }

        if (j == m)
            cout << i << " ";
    }
    cout << "비교횟수: " << comp << endl;
}
int comp1;
void initSP(char *p)
{
    int i, j, m = strlen(p);
    SP = new int[m];
    SP[0] = -1;
    for (i = 1, j = -1; i <= m - 1; i++)
    {
        while ((j >= 0) && (p[j + 1] != p[i]))
            j = SP[j];

        if (p[j + 1] == p[i])
            j++;

        SP[i] = j;
    }
}

void kmpsearch(char *p, char *a)
{
    int i, j, m = strlen(p), n = strlen(a);
    initSP(p);
    for (i = 0, j = -1; i <= n - 1; i++)
    {
        while ((j >= 0) && (p[j + 1] != a[i]))
        {
            comp1++;
            j = SP[j];
        }
        comp1++;
        if (p[j + 1] == a[i])
            j++;
        if (j == m - 1)
        {
            // 결과값 출력
            cout << i - m + 1 << " ";
            j = SP[j];
        }
    }
    cout << "비교횟수: " << comp1 << endl;
}

int index(char c)
{
    return c - 'A';
}

void rksearch(char *p, char *a)
{
    int comp = 0;
    int i, j, dM = 1, h1 = 0, h2 = 0, flag = 0;
    int m = strlen(p), n = strlen(a);
    for (i = 1; i < m; i++)
        dM = (d * dM) % q;
    for (i = 0; i < m; i++)
    {
        h1 = (h1 * d + index(p[i])) % q;
        h2 = (h2 * d + index(a[i])) % q;
    }
    for (i = 0; i < n - m + 1; i++)
    {
        comp++;
        if (h1 == h2)
        {
            flag = 1;
            for (j = i; j < i + m; j++)
            {
                comp++;
                if (a[j] != p[j - i])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
                cout << i << " "; // 결과값 출력
        }
        if (i < n - m)
        {
            h2 = (h2 - index(a[i]) * dM) % q;
            h2 = (h2 * d + index(a[i + m])) % q;
        }
    }
    cout << "비교횟수: " << comp << endl;
}

int main()
{
    char text[200] = {0};
    char pattern[200] = {0};
    cin.getline(text, 200);
    cin.getline(pattern, 200);
    cout << "Brute-Force" << endl;
    brutesearch(pattern, text);
    cout << "KMP" << endl;
    kmpsearch(pattern, text);
    cout << "Rabin_Karp_Search" << endl;
    rksearch(pattern, text);
}