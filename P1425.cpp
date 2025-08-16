#include <bits/stdc++.h>

using namespace std;

int a, b, c, d;

int main(){
    cin >> a >> b >> c >> d;
    cout << (d > b ? c - a : c - a - 1) << ' ' << (d > b ? d - b : d - b + 60) << endl;
    return 0;
}