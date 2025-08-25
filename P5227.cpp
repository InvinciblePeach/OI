#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10, MAXM = 2e5 + 10;
int n, m, q, fa[MAXN], tot, nxt[MAXM], val[MAXM], head[MAXM], to[MAXM], id[MAXM], v[MAXN];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int x) {
    if (fa[x] == x) return x;
    return fa[x] = get(fa[x]);
}

void add(int u, int v, int id) {
    nxt[++tot] = head[u];
    to[head[u] = tot] = v;
    ::id[tot] = id;
}

void adde(int u, int v, int id) { add(u, v, id), add(v, u, id); }

void dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        if (to[i] == fa[u]) continue;
        fa[to[i]] = u;
        dfs(to[i]);
        v[u] ^= (val[id[i]] = v[to[i]]);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    cerr << rnd() << ' ' << rnd() << ' ' << rnd() <<'\n';
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if (get(u) == get(v)) ::v[u] ^= (val[i] = rnd()), ::v[v] ^= val[i];
        else adde(u, v, i), fa[fa[u]] = fa[v];
    }
    fa[1] = 1;
    dfs(1);
    cin >> q;
    while (q --> 0) {
        static int x, y, z, w;
        cin >> x;
        if (x == 1) {
            cin >> y;
            if (val[y])
                puts("Connected");
            else
                puts("Disconnected");
        } else if (x == 2) {
            cin >> y >> z;
            if ((val[y]) && (val[y] ^ val[z]) && (val[z]))
                puts("Connected");
            else
                puts("Disconnected");
        } else if (x == 3) {
            cin >> y >> z >> w;
            if ((val[y]) && (val[z]) && (val[w]) && (val[y] ^ val[z]) && (val[z] ^ val[w]) && (val[y] ^ val[w]) &&
                (val[y] ^ val[z] ^ val[w]))
                puts("Connected");
            else
                puts("Disconnected");
        } else {
            cin >> x >> y >> z >> w;
            if ((val[x]) && (val[y]) && (val[z]) && (val[w]) && (val[x] ^ val[y]) && (val[x] ^ val[z]) &&
                (val[x] ^ val[w]) && (val[z] ^ val[y]) && (val[w] ^ val[y]) && (val[z] ^ val[w]) &&
                (val[x] ^ val[y] ^ val[z]) && (val[x] ^ val[y] ^ val[w]) && (val[x] ^ val[w] ^ val[z]) &&
                (val[w] ^ val[y] ^ val[z]) && (val[x] ^ val[y] ^ val[z] ^ val[w]))
                puts("Connected");
            else
                puts("Disconnected");
        }
    }

    return 0;
}