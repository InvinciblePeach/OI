#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1 << 17, mod = 998244353;
int n, m, a[MAXN], b[MAXN], f[MAXN], g[MAXN];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod, b >>= 1;
    }
    return res;
}

void OR(int *f, int x) {
    for (int len = 2, mid = 1; len <= m; len <<= 1, mid <<= 1)
        for (int i = 0; i < m; i += len)
            for (int j = 0; j < mid; j++)
                (f[i + j + mid] += f[i + j] * x) %= mod;
}

void AND(int *f, int x) {
    for (int len = 2, mid = 1; len <= m; len <<= 1, mid <<= 1)
        for (int i = 0; i < m; i += len)
            for (int j = 0; j < mid; j++)
                (f[i + j] += f[i + j + mid] * x) %= mod;
}

void XOR(int *f, int x) {
    for (int len = 2, mid = 1; len <= m; len <<= 1, mid <<= 1)
        for (int i = 0; i < m; i += len)
            for (int j = 0; j < mid; j++)
                (f[i + j] += f[i + j + mid]) %= mod, (f[i + j + mid] = f[i + j] - (f[i + j + mid] << 1)) %= mod,
                    (f[i + j] *= x) %= mod, (f[i + j + mid] *= x) %= mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    m = 1 << n;
    for (int i = 0; i < m; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];

    {
        memcpy(f, a, sizeof(a)), memcpy(g, b, sizeof(b));
        OR(f, 1), OR(g, 1);
        for (int i = 0; i < m; i++)
            (f[i] *= g[i]) %= mod;
        OR(f, -1);
        for (int i = 0; i < m; i++)
            cout << (f[i] + mod) % mod << " \n"[i == m - 1];
    }

    {
        memcpy(f, a, sizeof(a)), memcpy(g, b, sizeof(b));
        AND(f, 1), AND(g, 1);
        for (int i = 0; i < m; i++)
            (f[i] *= g[i]) %= mod;
        AND(f, -1);
        for (int i = 0; i < m; i++)
            cout << (f[i] + mod) % mod << " \n"[i == m - 1];
    }
    
    {
        memcpy(f, a, sizeof(a)), memcpy(g, b, sizeof(b));
        XOR(f, 1), XOR(g, 1);
        for (int i = 0; i < m; i++)
            (f[i] *= g[i]) %= mod;
        XOR(f, qpow(2, mod - 2));
        for (int i = 0; i < m; i++)
            cout << (f[i] + mod) % mod << " \n"[i == m - 1];
    }
    return 0;
}