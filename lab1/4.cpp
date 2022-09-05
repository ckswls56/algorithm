#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
vector <int>a;
vector <int>b;
void print_vec(const vector<int> &vec){
    for(const int &it : vec){
        cout << it << ", ";
    }
    cout <<"\n";
}

void print_union(){
    vector<int> buff(a.size()+b.size());
    auto iter = set_union(a.begin(),a.end(),b.begin(),b.end(),buff.begin());
    buff.erase(iter,buff.end());

    print_vec(buff);
}

void print_intersection(){
    vector<int> buff(a.size()+b.size());
    auto iter = set_intersection(a.begin(),a.end(),b.begin(),b.end(),buff.begin());
    buff.erase(iter,buff.end());

    print_vec(buff);
}

int main(){
    int n,m;

    cin >> n >> m;
    for(int i=0;i<n;i++){
        a.push_back(rand());
    }
    for(int i=0;i<m;i++){
        b.push_back(rand());
    }

    cout<<"���� A- ";
    print_vec(a);
    cout<<"���� B- ";
    print_vec(b);
    cout<<"������- ";
    print_union();
    cout<<"������- ";
    print_intersection();
}