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
    auto end = --(vec.end()); // vec 마지막 index
    for (auto it = vec.begin(); it != end; it++)
    {
        cout << " " << *it << ",";
    }
    //중간에는 ,출력
    cout << " " << *end << "\n";
}

void print_union()
{
    vector<int> buff(a.size() + b.size());                                       // a집합과 b집합의 size를 더한만큼 생성
    auto iter = set_union(a.begin(), a.end(), b.begin(), b.end(), buff.begin()); //합집합 생성
    buff.erase(iter, buff.end());                                                //빈공간 제거

    print_vec(buff); // ?????? ???
}

void print_intersection()
{
    vector<int> buff(a.size() + b.size());
    auto iter = set_intersection(a.begin(), a.end(), b.begin(), b.end(), buff.begin()); //교집합 생성
    buff.erase(iter, buff.end());
    if (buff.size()) //교집합이 있다면 교집합 출력
        print_vec(buff);
    else // 없으면 x출력
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
    { // set size가 n이 될떄까지 난수 입력
        tmp1.insert(rand() + 1);
    }
    copy(tmp1.begin(), tmp1.end(), back_inserter(a));

    while (tmp2.size() != m)
    { // set size가 m이될떄까지 난수 입력
        tmp2.insert(rand() + 1);
    }
    copy(tmp2.begin(), tmp2.end(), back_inserter(b));

    sort(a.begin(), a.end()); // a정렬
    sort(b.begin(), b.end()); // b정렬

    cout << "집합 A - ";
    print_vec(a);
    cout << "집합 B - ";
    print_vec(b);
    cout << "합집합 - ";
    print_union();
    cout << "교집합 - ";
    print_intersection();
}