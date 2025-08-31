#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10;
int n, m, k, q, a[MAXN];
struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void addedge(int u, int v, int w) { g[u].emplace_back(v, w), g[v].emplace_back(u, w); }

namespace kruskal {
    int fa[MAXN], l[MAXN], r[MAXN];
    struct Edge {
        int u, v, w;
        bool operator<(const Edge &o) const { return w < o.w; }
    } e[MAXN];

    int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

    void merge(int a, int b) { fa[get(a)] = get(b); }

    void work() {
        for (int i = 1; i <= n; i++) l[i] = r[i] = fa[i] = i;
        sort(e + 1, e + m + 1);
        for (int i = 1; i <= m; i++) {
            auto [u, v, w] = e[i];
            if (get(u) == get(v)) continue;
            int fau = get(u), fav = get(v);
            addedge(r[fau], l[fav], w);
            fa[fav] = fau, r[fau] = r[fav];
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
    for (auto [v, w] : g[u]) {
        if (v == fa) continue;
        if (a[v] ^ a[u]) Heap::insert(w);
        dfs(v, u);
    }
}

signed main() {
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
        for (auto [v, w] : g[u]) {
            if (a[v] == x) Heap::erase(w);
            if (a[v] == a[u]) Heap::insert(w);
        }
        a[u] = x;
        cout << Heap::top() << '\n';
    }

    return 0;
}