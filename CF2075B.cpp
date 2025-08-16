#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 5010;
int t, n, k, a[MAXN];

struct Pair {
    int val, pos;

    Pair() {}
    Pair(const int &V, const int &P) : val(V), pos(P) {}
    bool operator<(const Pair &o) const { return val < o.val; }
};
priority_queue<Pair> q1;
struct Tri {
    int val, l, r;

    Tri() {}
    Tri(const int &V, const int &L, const int &R) : val(V), l(L), r(R) {}
    bool operator<(const Tri &o) const { return val < o.val; }
};
priority_queue<Tri> q2;
bitset<MAXN> use;

void solve() {
    int ans = 0, mx = INT_MIN, id = 0;
    use.reset();
    cin >> n >> k;
    while (q1.size()) q1.pop();
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        q1.emplace(a[i], i);
        if (a[i] > mx) a[i] = mx, id = 0;
    }
    if (k == 1) {
        cout << q1.top().val;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) solve();

    return 0;
}