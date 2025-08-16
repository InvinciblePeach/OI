#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, a[MAXN];
struct Node {
    ll sum;
    int l, r;

    Node() {}
    Node(ll Sum, int L, int R) : sum(Sum), l(L), r(R) {}

    bool operator<(const Node &o) const { return sum > o.sum; }
};
priority_queue<Node> q;
bitset<MAXN> del;
ll ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], ans += a[i];
    for (int i = 1; i < n; i++)
        q.emplace(a[i] + a[i + 1], i, i + 1);
    while (!q.empty()) {
        auto [val, l, r] = q.top();
        q.pop();
        if (del[l] || del[r]) continue;
        if (val >= 0) break;

        ans -= val;
        del[l] = del[r] = 1;
        if (l - 1 >= 1 && r + 1 <= n) q.emplace(a[l - 1] + a[r + 1], l - 1, r + 1);
    }
    cout << ans << '\n';

    return 0;
}