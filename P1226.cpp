#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;

int a, b, p;

int quick_power(const int & x, const int &y ) {
    if (y == 1) {
        return x;
    } else if (y == 0) {
        return 1;
    }

    int tmp = quick_power(x, y >> 1u) % p;
    return tmp * tmp % p * (y % 2 == 0 ? 1 : x) % p;
}

signed main() {
    cin >> a >> b >> p;
    cout << a << '^' << b << " mod " << p << '=' << quick_power(a, b) % p;
    return 0;
}