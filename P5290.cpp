#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, a[MAXN], ans;
int q[MAXN], top;
vector<int> g[MAXN];
priority_queue<int> pq[MAXN];

void merge(int x, int y) {
    if (pq[x].size() < pq[y].size()) swap(pq[x], pq[y]);
    while (!pq[y].empty()) {
        q[++top] = max(pq[x].top(), pq[y].top());
        pq[x].pop(), pq[y].pop();
    }
    while (top) pq[x].emplace(q[top--]);
}

void dfs(int u) {
    for (auto v : g[u])
        dfs(v), merge(u, v);
    pq[u].emplace(a[u]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2, fa; i <= n; i++) cin >> fa, g[fa].emplace_back(i);
    dfs(1);
    while (!pq[1].empty()) ans += pq[1].top(), pq[1].pop();
    cout << ans << '\n';

    return 0;
}