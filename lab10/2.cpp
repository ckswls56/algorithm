#include <iostream>
using namespace std;
const int d = 26;
const int q = 33554393;
int comp;
void brutesearch(char p[][10], char a[][100])
{ // p : Pattern String, a : Text String
    int t, i, j, k, m = 10, n = 100;
    for (i = 0; i <= n - m; i++)
    {
        for (t = 0; t <= n - m; t++)
        {
            for (j = 0; j < m; j++)
            {
                for (k = 0; k < m; k++)
                {
                    comp++;
                    if (a[i + j][t + k] != p[j][k])
                        break;
                }
                if (k != m)
                {
                    break;
                }
            }
            if (j == m)
            {
                cout << t << "," << i << endl;
            }
        }
    }
}
int index(char c)
{
    return c - 'A';
}

void rksearch(char p[][10], char a[][100])
{
    int i, j, k, t, dM = 1, h1 = 0, h2 = 0, flag = 0;
    int m = 10, n = 100;
    for (k = 0; k < n - m + 1; k++)
    {
        dM = 1, h1 = 0, h2 = 0, flag = 0;
        for (i = 1; i < m * m; i++)
            dM = (d * dM) % q;
        for (i = 0; i < m; i++)
        {
            for (t = 0; t < m; t++)
            {
                h1 = (h1 * d + index(p[t][i])) % q;
                h2 = (h2 * d + index(a[k + t][i])) % q;
            }
        }
        for (i = 0; i < n - m + 1; i++)
        {
            comp++;
            if (h1 == h2)
            {
                flag = 1;
                for (j = i; j < i + m; j++)
                {
                    for (t = k; t < k + m; t++)
                    {
                        comp++;
                        if (a[t][j] != p[t - k][j - i])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (!flag)
                        break;
                }
                if (flag)
                {
                    cout << k << ", " << i << endl;
                } // 결과값 출력
            }
            if (i < n - m)
            {
                for (t = 0; t < m; t++)
                {
                    h2 = (h2 - index(a[k + t][i]) * dM) % q;
                    h2 = (h2 * d + index(a[k + t][i + m])) % q;
                }
            }
        }
    }
}
int main()
{
    char text[100][100] = {0};
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            text[i][j] = 'A';
        }
    }
    char pattern[10][10] = {0};
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            pattern[i][j] = 'A';
        }
    }
    pattern[9][9] = 'B';

    brutesearch(pattern, text);
    cout << comp << "Burte-Force" << endl;
    comp = 0;

    rksearch(pattern, text);
    cout << comp << "Rabin-Karp" << endl;
}