#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;
int n, m, q, pos[MAXN], fa[MAXN], cnt;
unordered_set<int> g[MAXN];
struct Edge {
    int u, v;
} e[MAXN];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

void merge(int x, int y) { fa[get(x)] = get(y); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = pos[i] = i;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v;
        g[e[i].u].emplace(e[i].v), g[e[i].v].emplace(e[i].u);
    }
    cnt = m;
    cin >> q;
    while (q --> 0) {
        static int x;
        cin >> x;
        auto [a, b] = pair<int, int>(get(pos[e[x].u]), get(pos[e[x].v]));
        if ((a ^ b) && g[a].count(b)) {
            cnt--;
            if (g[a].size() > g[b].size()) swap(a, b);
            for (auto v : g[a]) {
                if (v == b) continue;
                if (g[b].count(v)) {
                    cnt--;
                } else g[b].emplace(v);
                g[v].erase(a);
                g[v].emplace(b);
            }
            g[a].clear();
            merge(a, b);
            pos[e[x].u] = pos[e[x].v] = get(a);
        }
        cout << cnt << '\n';
    }

    return 0;
}