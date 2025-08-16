#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n, rt, siz[MAXN], f[MAXN], dep[MAXN], sum;
vector<int> g[MAXN];
bitset<MAXN> vis;

void dfs1(int u, int fa) {
    siz[u] = 1;
    sum += dep[u];
    for (auto v : g[u]) {
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        siz[u] += siz[v];
    }
}

void dfs2(int u, int fa) {
    for (auto v : g[u]) {
        if (v == fa) continue;
        f[v] = f[u] + (n - 2 * siz[v]);
        dfs2(v, u);
    }
}

void out(int u, int fa) {
    for (auto v : g[u]) {
        if (v == fa) continue;
        cout << v << ' ' << u << '\n';
        out(v, u);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        vis.reset();
        sum = 0;
        for (int i = 1; i <= n; i++)
            g[i].clear(), siz[i] = f[i] = dep[i] = 0;
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        if (n <= 2) {
            cout << "NO\n";
            continue;
        }
        dfs1(1, 1);
        f[1] = sum;
        dfs2(1, 1);
        for (int i = 1; i <= n; i++) {
            if (f[i] == n) {
                rt = i;
                break;
            }
        }
        cout << "YES\n";
        out(rt, rt);
    }

    return 0;
}