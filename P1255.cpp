#include <bits/stdc++.h>

using namespace std;

int n;
unsigned long long a = 1, b = 1;

int main(){
    cin >> n;
    for (int i = 3; i <= n + 1; i++){
        unsigned long long c = a;
        a += b;
        b = c;
    }
    cout << a;
    return 0;
}