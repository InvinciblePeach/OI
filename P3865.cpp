#include <bits/stdc++.h>

using namespace std;

int n, m, f[1000005][30];
unsigned int logs[1000005];

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

int main(){

    n = read(), m = read();
    for (int i = 1; i <= n; i++){
        f[i][0] = read();
    }

    logs[1] = 0;
    for (int i = 2; i <= n; i++){
        logs[i] = logs[i / 2] + 1;
    }

    for (unsigned int j = 1; j <= 25; j++){
        for (int i = 1; i + (1u << j) - 1 <= n; i++){
            f[i][j] = max(f[i][j - 1], f[i + (1u << (j - 1))][j - 1]);
        }
    }

    for (int i = 1; i <= m; i++){
        int l = read(), r = read();
        unsigned int s = logs[r - l + 1];
        printf("%d\n", max(f[l][s], f[r - (1u << s) + 1][s]));
    }

    return 0;
}