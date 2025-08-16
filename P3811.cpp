#include <bits/stdc++.h>

using namespace std;

int n, p;
long long inv[3000005];

inline int read() {
    char c = char(getchar());
    int x = 0, flag = 1;
    while (c < '0' || c > '9') {
        if (c == '-') flag = -1;
        c = char(getchar());
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = char(getchar());
    }
    return x * flag;
}

int main() {
    n = read(), p = read();
    inv[1] = 1;
    printf("%d\n", 1);
    for (int i = 2; i <= n; i ++) {
        inv[i] = (long long)(p - p / i) * inv[p % i] % p;
        printf("%d\n", inv[i]);
    }
    return 0;
}