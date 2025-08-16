#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10, MAXV = 1e6 + 10;
int n, q, fa[20][MAXN], ans[MAXN], dep[MAXN];
string w[MAXN];
gp_hash_table<string, int> cnt;

struct Edge {
    int v;
    string w;

    Edge(int V, const string &W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

struct Query {
    int id, val;
    string s;
    Query(int ID, int V, const string &S) : id(ID), val(V), s(S) {}
};
vector<Query> qry[MAXN];

void dfs1(int u) {
    for (int i = 1; i < 20; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (auto [v, w] : g[u]) {
        if (v == fa[0][u]) continue;
        fa[0][v] = u;
        dep[v] = dep[u] + 1;
        ::w[v] = w;
        dfs1(v);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 19; ~i; i--)
        if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 19; ~i; i--)
        if (fa[i][a] ^ fa[i][b]) a = fa[i][a], b = fa[i][b];
    return fa[0][a];
}

void dfs2(int u) {
    string s = "";
    for (int i = 0; i < w[u].size(); i++) cnt[s += w[u][i]]++;
    for (auto [id, val, s] : qry[u]) ans[id] += val * cnt[s];
    for (auto [v, w] : g[u]) {
        if (v == fa[0][u]) continue;
        dfs2(v);
    }
    s = "";
    for (int i = 0; i < w[u].size(); i++) cnt[s += w[u][i]]--;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cerr << __cplusplus << '\n';
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        static string s;
        cin >> u >> v >> s;
        g[u].emplace_back(v, s);
        g[v].emplace_back(u, s);
    }
    dep[1] = 1, dfs1(1);
    cin >> q;
    for (int i = 1, u, v; i <= q; i++) {
        static string s;
        cin >> u >> v >> s;
        qry[u].emplace_back(i, 1, s);
        qry[v].emplace_back(i, 1, s);
        qry[lca(u, v)].emplace_back(i, -2, s);
    }
    dfs2(1);
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';

    return 0;
}