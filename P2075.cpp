#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10, S = 320;
int n, m, a[MAXN], q[MAXN], ans[MAXN];
int bl[MAXN], L[S], R[S];

struct Query {
    int l, r, id;

    bool operator<(const Query &o) const { return r < o.r; }
} qry[MAXN];

struct Fenwick {
    int t[MAXN];

    constexpr int lowbit(const int &x) { return x & -x; }

    void add(int x, int val) {
        for (x++; x <= n + 1; x += lowbit(x)) t[x] += val;
    }

    int query(int x) {
        int res = 0;
        for (x++; x; x -= lowbit(x)) res += t[x];
        return res;
    }
} T;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++)
        cin >> qry[i].l >> qry[i].r, qry[i].id = i;

    memset(L, 0x7f, sizeof(L));
    for (int i = 1; i <= n; i++) bl[i] = (i - 1 + S) / S, L[bl[i]] = min(L[bl[i]], i), R[bl[i]] = max(R[bl[i]], i);

    T.add(0, n);
    for (int i = 1; i <= n; i++) {
        int &val = a[i];

        if (val + 1 <= n) {
            
        }
    }

    return 0;
}