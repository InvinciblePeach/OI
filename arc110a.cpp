#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, res = 1;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int lcm(int a, int b) { return a / gcd(a, b) * b; }

signed main() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        res = lcm(res, i);
    }
    cout << res + 1 << '\n';
    return 0;
}