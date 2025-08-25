#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 2e5 + 10;
int n, w[MAXN << 1], tot;
vector<int> t[MAXN];

namespace kruskal {
    int fa[MAXN];
    struct Edge {
        int u, v, w;
        bool operator<(const Edge &o) const { return w < o.w; }
    } e[MAXN];

    int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

    void merge(int a, int b) { fa[get(a)] = get(b); }

    int newnode(int x) {
        w[++tot] = x;
        return tot;
    }

    void build() {
        memset(w, 0x3f, sizeof(w));
        tot = n;
        for (int i = 1; i <= (n << 1); i++) fa[i] = i;
        sort(e + 1, e + n);
        for (int i = 1; i < n; i++) {
            auto [u, v, w] = e[i];
            if (get(u) == get(v)) continue;
            int fau = get(u), fav = get(v);
            int p = newnode(w);
            t[p].emplace_back(fau);
            t[p].emplace_back(fav);
            fa[fau] = fa[fav] = p;
        }
    }
} // namespace kruskal
using namespace kruskal;

int ans = 0;
void dfs(int u, int mx = INT_MAX) {
    mx = min(mx, w[u]);
    for (auto v : t[u]) dfs(v, mx), cerr << u << ' ' << v << '\n';
    if (t[u].empty()) ans += mx;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i < n; i++) cin >> e[i].u >> e[i].v >> e[i].w;
    build();
    for (int i = 1; i <= tot; i++) cerr << w[i] << " \n"[i == tot];
    dfs(tot);
    cout << ans << '\n';

    return 0;
}