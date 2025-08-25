#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10, MAXM = 4e5 + 10;
int n, m, k, q, a[MAXN];
struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> t[MAXN];

namespace kruskal {
    struct Edge {
        int u, v, w;
        bool operator<(const Edge &o) const { return w < o.w; }
    } e[MAXM];

    int fa[MAXN];
    int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
    void merge(int x, int y) { fa[get(x)] = get(y); }

    void work() {
        for (int i = 1; i <= n; i++) fa[i] = i;
        sort(e + 1, e + m + 1);
        for (int i = 1; i <= m; i++) {
            auto [u, v, w] = e[i];
            if (get(u) == get(v)) continue;
            t[u].emplace_back(v, w);
            t[v].emplace_back(u, w);
            merge(u, v);
        }
    }
} // namespace kruskal
using kruskal::work, kruskal::e;

namespace Heap {
    priority_queue<int, vector<int>, greater<>> q, del;

    void insert(int x) { q.emplace(x); }
    void erase(int x) { del.emplace(x); }
    int top() {
        while (!del.empty() && q.top() == del.top()) q.pop(), del.pop();
        return q.top();
    }
} // namespace Heap

void dfs(int u, int fa) {
    for (auto [v, w] : t[u]) {
        if (v == fa) continue;
        if (a[v] ^ a[u]) Heap::insert(w);
        dfs(v, u);
    }
}

signed main() {
    freopen("war.in", "r", stdin);
    freopen("war.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k >> q;
    for (int i = 1, u, v, w; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
    work();
    for (int i = 1; i <= n; i++) cin >> a[i];
    dfs(1, 0);
    while (q-- > 0) {
        static int u, x;
        cin >> u >> x;
        for (auto [v, w] : t[u]) {
            if (a[v] == x) Heap::erase(w);
            if (a[v] == a[u]) Heap::insert(w);
        }
        a[u] = x;
        cout << Heap::top() << '\n';
    }
    return 0;
}