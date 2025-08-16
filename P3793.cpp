#include <bits/stdc++.h>

typedef unsigned long long ull;
using namespace std;
const uint MAXN = 2e7 + 10, S = 4775;
uint n, m, seed, s, bl[MAXN], a[MAXN], pre[MAXN], suf[MAXN], st[S][14];
ull ans;

namespace GenHelper {
    unsigned z1, z2, z3, z4, b;
    unsigned rand_() {
        b = ((z1 << 6) ^ z1) >> 13;
        z1 = ((z1 & 4294967294U) << 18) ^ b;
        b = ((z2 << 2) ^ z2) >> 27;
        z2 = ((z2 & 4294967288U) << 2) ^ b;
        b = ((z3 << 13) ^ z3) >> 21;
        z3 = ((z3 & 4294967280U) << 7) ^ b;
        b = ((z4 << 3) ^ z4) >> 12;
        z4 = ((z4 & 4294967168U) << 13) ^ b;
        return (z1 ^ z2 ^ z3 ^ z4);
    }
}

void srand(unsigned x) {
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
}

int read() {
    using namespace GenHelper;
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> seed;
    s = (n - 1) / S + 1;
    srand(seed);
    for (uint i = 1; i <= n; i++)
        a[i] = read(), bl[i] = (n - 1) / S + 1;

    for (uint i = 1; i <= s; i++) {
        int L = (i - 1) * S + 1, R = min(n, i * S);
        pre[L] = a[L], suf[R] = a[R];
        for (int j = L + 1; j <= R; j++)
            pre[j] = max(pre[j - 1], a[j]);
        for (int j = R - 1; j >= L; j--)
            suf[j] = max(suf[j + 1], a[j]);
    }

    for (uint i = 1; i <= s; i++)
        st[i][0] = pre[min(n, i * S)];
    for (uint i = 1; i < 14; i++)
        for (uint j = 1; j <= s; j++)
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    
    while (m --> 0) {
        uint l = read() % n + 1, r = read() % n + 1;
        if (l > r) swap(l, r);
        uint L = (l - 1) / S + 1, R = (r - 1) / S + 1, res = 0;
        if (L == R) {
            for (int i = l; i <= r; i++) res = max(res, a[i]);
            ans += res;
            continue;
        }
        uint nw = L + 1;
        for (int i = 13; ~i; i--)
            if (nw + (1 << i) <= R) res = max(res, st[nw][i]), nw += 1 << i;
        res = max({res, suf[l], pre[r]});
        ans += res;
    }
    cout << ans << '\n';
    return 0;
}
