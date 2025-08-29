#include <bits/stdc++.h>
#define lc(p) (p << 1)
#define rc(p) (p << 1 | 1)
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10, MAXM = 4.2e6 + 10;
int n, m, p, id[MAXN];
struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXM];

void buildin(int p, int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    buildin(lson), buildin(rson);
    g[p].emplace_back(lc(p), 0);
    g[p].emplace_back(rc(p), 0);
}

void buildout(int p, int l, int r) {
    g[p].emplace_back(p + (n << 2), 0);
    if (l == r) return id[l] = p + (n << 2), void();
    int mid = (l + r) >> 1;
    buildout(lson), buildout(rson);
    g[lc(p) + (n << 2)].emplace_back(p + (n << 2), 0);
    g[rc(p) + (n << 2)].emplace_back(p + (n << 2), 0);
}

void update1(int p, int l, int r, int L, int R, int k) {
    if (L <= l && r <= R) return g[k].emplace_back(p, 1), g[p + (n << 2)].emplace_back(k + 1, 1), void();
    int mid = (l + r) >> 1;
    if (L <= mid) update1(lson, L, R, k);
    if (R > mid) update1(rson, L, R, k);
}

void update2(int p, int l, int r, int L, int R, int k) {
    if (L <= l && r <= R) return g[k + 1].emplace_back(p, 1), g[p + (n << 2)].emplace_back(k, 1), void();
    int mid = (l + r) >> 1;
    if (L <= mid) update2(lson, L, R, k);
    if (R > mid) update2(rson, L, R, k);
}

int dis[MAXM];
bitset<MAXM> vis;
deque<int> q;
void bfs(int s) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.emplace_front(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (w == 1)
                    q.emplace_back(v);
                else
                    q.emplace_front(v);
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> p;
    buildin(1, 1, n), buildout(1, 1, n);
    for (int i = 1, a, b, c, d; i <= m; i++) {
        cin >> a >> b >> c >> d;
        update1(1, 1, n, a, b, (n << 3) + (i << 1));
        update2(1, 1, n, c, d, (n << 3) + (i << 1));
    }
    bfs(id[p]);
    for (int i = 1; i <= n; i++)
        cout << (dis[id[i]] >> 1) << '\n';

    return 0;
}