#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;
vector<int> a;
vector<int> b;

void print_vec(const vector<int> &vec)
{
    auto end = --(vec.end());
    for (auto it = vec.begin(); it != end; it++)
    {
        cout << " " << *it << ",";
    }
    cout << " " << *end << "\n";
}

void print_union()
{
    vector<int> buff(a.size() + b.size());
    auto iter = set_union(a.begin(), a.end(), b.begin(), b.end(), buff.begin());
    buff.erase(iter, buff.end());

    print_vec(buff);
}

void print_intersection()
{
    vector<int> buff(a.size() + b.size());
    auto iter = set_intersection(a.begin(), a.end(), b.begin(), b.end(), buff.begin());
    buff.erase(iter, buff.end());
    if (buff.size())
        print_vec(buff);
    else
        cout << "X\n";
}

int main()
{
    int n, m;
    set<int> tmp1;
    set<int> tmp2;
    srand((unsigned int)time(NULL));
    cin >> n >> m;
    while (tmp1.size() != n)
    {
        tmp1.insert(rand() + 1);
    }
    copy(tmp1.begin(), tmp1.end(), back_inserter(a));

    while (tmp2.size() != m)
    {
        tmp2.insert(rand() + 1);
    }
    copy(tmp2.begin(), tmp2.end(), back_inserter(b));

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    cout << "집합A- ";
    print_vec(a);
    cout << "집합B- ";
    print_vec(b);
    cout << "합집합- ";
    print_union();
    cout << "교집합- ";
    print_intersection();
}