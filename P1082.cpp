#include <bits/stdc++.h>

using namespace std;

long long a, b, tmp = 1;

int main() {
    cin >> a >> b;
    while (tmp % a) { tmp += b; }
    cout << tmp / a << endl;
    return 0;
}