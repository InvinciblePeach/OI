#include <bits/stdc++.h>
#define int long long

using namespace std;

const int mod = 123456789;
int T;

inline int read() {
    char c = char(getchar());
    int x = 0, flag = 1;
    while (c < '0' || c > '9') {
        if (c == '-') flag = -1;
        c = char(getchar());
    }
    while (c >= '0' && c <= '9') {
        x = (x * 10 % mod + c - '0') % mod;
        c = char(getchar());
    }
    return x * flag;
}

signed main() {
    T = read();
    while (T-- > 0) {
        int a = read(), b = read(), c = read();
        if (a * b % mod == c) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}