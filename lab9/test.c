#include <stdio.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int abs(int a)
{
    if (a < 0)
        return -a;
    return a;
}

int main()
{
    int x;
    scanf("%d", &x);
    int a = 1;
    int b = 100000000;
    int m = a + b / 2;
    printf("%d", max(10, 10 * (x - m) / max(abs(m - a), abs(m - b))));
}