#include <bits/stdc++.h>
#define rep(x, y, z) for (int x = (y); x <= z; x++)
#define per(x, y, z) for (int x = (y); x >= z; x--)

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10;
int n, m, k, S, bl[MAXN], a[MAXN], ans[MAXN];
vector<int> b;

struct Query {
    int l, r, id;

    bool operator<(const Query &o) { return bl[l] == bl[o.l] ? r < o.r : l < o.l; }
} q[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, m) cin >> q[i].l >> q[i].r, q[i].id = i;
    if (k > 14) {
        rep(i, 1, m) cout << "0\n";
        return 0;
    }
    rep(i, 0, 16383) if (__builtin_popcount(i) == k) b.emplace_back(i);
    S = sqrt(n);
    rep(i, 1, n) bl[i] = (i - 1) / S + 1;
    sort(q + 1, q + 1 + m);

    return 0;
}