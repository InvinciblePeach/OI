#include <bits/stdc++.h>
using namespace std;

#define int long long
const int maxn = 1e6 + 10;
const int maxm = 5e3 + 10;
const int mod = 998244353;

namespace IO {
void openfile() {
#ifndef ONLINE_JUDGE
#endif
}

int mul(int x, int y) {
    return 1ll * x * y % mod;
}

int add(int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int sub(int x, int y) {
    return add(x, mod - y);
}

inline int read() {
    int x = 0, f = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        x = x * 10 + c - '0', c = getchar();
    if (f)
        x = -x;
    return x;
}
}  // namespace IO
using namespace IO;

int f[maxm][maxm];
int n, a[maxn];

signed main() {
    openfile();
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    int b = 1 << 8;
    for (int i = 0; i < b; i++)
        f[0][i] = 1;
    for (int i = 1; i <= n; i++) {
        int p = a[i] % b, q = a[i] / b, ans = 0;
        for (int j = p;; j = (j - 1) & p) {
            ans = add(ans, f[j][q]);
            if (!j)
                break;
        }
        q ^= 255;
        for (int j = q;; j = (j - 1) & q) {
            f[p][j ^ 255] = add(f[p][j ^ 255], ans);
            if (!j)
                break;
        }
        printf("%lld\n", ans);
    }
    return 0;
}