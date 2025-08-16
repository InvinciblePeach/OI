#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
constexpr int MAXN = 5e4 + 10, MAXV = 80;
int n, q;
ll a[MAXN];
bitset<MAXN> vis[MAXV];

struct Fenwick {
    ll t[MAXN];

    constexpr int lowbit(const int &x) { return x & -x; }

    void add(int x, ll val) {
        for (; x <= n; x += lowbit(x)) t[x] ^= val;
    }

    ll query(int x) {
        ll res = 0;
        for (; x; x -= lowbit(x)) res ^= t[x];
        return res;
    }

    ll query(int l, int r) { return query(r) ^ query(l - 1); }
} val, b[MAXV];

struct LB {
    ll a[61];

    void clear() { memset(a, 0, sizeof(a)); }

    void insert(ll x) {
        for (int i = 60; ~i; i--) {
            if (x >> i & 1) {
                if (!a[i]) {
                    a[i] = x;
                    break;
                }
                x ^= a[i];
            }
        }
    }

    ll query(ll val) {
        for (int i = 60; ~i; i--) {
            val = max(val, val ^ a[i]);
        }
        return val;
    }
} ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, t; i <= n; i++) {
        t = a[i - 1] ^ a[i];
        for (int j = 0; j < MAXV; j++)
            if (vis[j][i] = (rnd() & 1)) b[j].add(i, t);
        val.add(i, t);
    }
    while (q-- > 0) {
        static int op, l, r;
        static ll v;
        cin >> op >> l >> r >> v;
        if (op == 1) {
            val.add(l, v), val.add(r + 1, v);
            for (int i = 0; i < MAXV; i++) {
                if (vis[i][l]) b[i].add(l, v);
                if (r + 1 <= n && vis[i][r + 1]) b[i].add(r + 1, v);
            }
        } else {
            ans.clear();
            for (int i = 0; i < MAXV; i++) ans.insert(b[i].query(l + 1, r));
            ans.insert(val.query(l));
            cout << ans.query(v) << '\n';
        }
    }
}