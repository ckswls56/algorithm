#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int **D;
int EditDist(int n, string X, int m, string Y, int ins, int del, int chg)
{
    // n : X의 길이, m : Y의 길이, ins : 삽입비용, del : 삭제비용, chg : 변경비용
    D[0][0] = 0;
    int c;

    for (int i = 1; i < n + 1; i++)
        D[i][0] = D[i - 1][0] + del; //첫 열의 초기화
    for (int j = 1; j < m + 1; j++)
        D[0][j] = D[0][j - 1] + ins; // 첫 행의 초기화

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            c = (X[i - 1] == Y[j - 1]) ? 0 : chg;
            D[i][j] = min({D[i - 1][j] + del, D[i][j - 1] + ins, D[i - 1][j - 1] + c});
        }
    }
    return D[n][m];
}

void reverseDP(string X, int i, string Y, int j)
{
    string str;
    while (i != 0 || j != 0)
    {
        if (i == 0)
        {
            str = "I " + str;
            j--;
            continue;
        }
        if (j == 0)
        {
            str = "D " + str;
            i--;
            continue;
        }

        if (D[i - 1][j - 1] < D[i - 1][j] && D[i - 1][j - 1] < D[i][j - 1])
        {
            if (D[i - 1][j - 1] == D[i][j])
                str = "O " + str;
            else
                str = "C " + str;
            i--;
            j--;
        }
        else if (D[i][j - 1] < D[i - 1][j])
        {
            str = "I " + str;
            j--;
        }
        else
        {
            str = "D " + str;
            i--;
        }
    }
    cout << "Min Edit Path: " << str << endl;
}

int main()
{
    string x, y;
    cout << "input source string :";
    cin >> x;
    cout << "input target string :";
    cin >> y;

    D = new int *[x.length() + 1];

    for (int i = 0; i <= x.length(); i++)
    {
        D[i] = new int[y.length() + 1];
    }
    int res = EditDist(x.length(), x, y.length(), y, 1, 1, 2);

    cout << "Edit Table" << endl;
    for (int i = 0; i <= x.length(); i++)
    {
        for (int j = 0; j <= y.length(); j++)
        {
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
    reverseDP(x, x.length(), y, y.length());
}