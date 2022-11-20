#include <iostream>
#include <cstring>
using namespace std;
int *SP; // SP�� ���� �޸𸮴� p�� ũ�⸸ŭ ���� �Ҵ� �ؾ��Ѵ�.
int *skip;
const int q = 33554393;
const int d = 26;
const int alphabet_count = 26;
int lp[26];
int comp2;

int index(char c)
{
    return c - 'A';
}
void initSP(char *p)
{
    int i, j, m = strlen(p);
    SP = new int[m];
    SP[0] = -1;
    j = -1;
    for (i = 1; i <= m - 1; i++)
    {
        while ((j >= 0) && (p[j + 1] != p[i]))
        {
            j = SP[j];
        }
        if (p[j + 1] == p[i])
        {
            j++;
        }
        SP[i] = j;
    }
}

void LastPos(char *p)
{
    int i;
    for (i = 0; i < alphabet_count; i++)
        lp[i] = -1;
    for (i = 0; i < strlen(p); i++)
        lp[index(p[i])] = i;
}

void GoodSuffix(char *p)
{
    int i, k, m = strlen(p);
    char *r_p = new char[m];

    for (i = 0; i < m; i++)
    {
        r_p[m - i - 1] = p[i];
    }

    initSP(r_p);

    for (i = -1; i <= m - 1; i++)
        skip[i] = m - 1 - SP[m - 1];
    for (k = 0; k <= m - 1; k++)
    {
        i = m - 1 - SP[k] - 1;
        if (skip[i] > k - SP[k])
            skip[i] = k - SP[k];
    }
}
void BoyerMoore(char *p, char *a)
{

    int i, j, m = strlen(p), n = strlen(a);
    LastPos(p);
    GoodSuffix(p);
    j = 0;
    while (j <= n - m)
    {
        comp2++;
        for (i = m - 1; i >= 0 && p[i] == a[j + i]; i--)
        {
            comp2++;
        };
        if (i == -1)
        {
            cout << j << " ";
            j = j + skip[-1];
        }
        else
        {
            j = j + max(skip[i], i - lp[index(a[j + i])]);
        }
    }
    cout << endl
         << "��Ƚ��: " << comp2 << endl;
}

void brutesearch(char *p, char *a)
{ // p : Pattern String, a : Text String
    int comp = 0;
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
        {
            cout << i << " ";
        }
    }
    cout << endl
         << "��Ƚ��: " << comp << endl;
}
void kmpsearch(char *p, char *a)
{
    int i, j, m = strlen(p), n = strlen(a);
    initSP(p);
    j = -1;
    for (i = 0; i <= n - 1; i++)
    {
        while ((j >= 0) && (comp2++, p[j + 1] != a[i]))
        {
            j = SP[j];
        }
        if (p[j + 1] == a[i])
        {
            j++;
            comp2++;
        }
        if (j == m - 1)
        {
            // ����� ���
            cout << i - m + 1 << " ";
            j = SP[j];
        }
    }
    cout << endl
         << "��Ƚ��: " << comp2 << endl;
}

int main()
{
    char text[10000];
    char pattern[100];
    cin.getline(text, 10000);
    cin.getline(pattern, 100);

    skip = new int[strlen(pattern)];
    comp2 = 0;
    cout << "Boyer" << endl;
    BoyerMoore(pattern, text);
    comp2 = 0;
    cout << endl
         << "brute" << endl;
    brutesearch(pattern, text);
    comp2 = 0;
    cout << endl
         << "kmp" << endl;
    kmpsearch(pattern, text);
}
