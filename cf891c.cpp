#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int n, m, q, fa[MAXN], siz[MAXN], st[MAXN], top;

int get(int x) {
    if (fa[x] == x) return x;
    return fa[x] = get(fa[x]);
}

void merge(int u, int v) { fa[get(u)] = fa[get(v)]; }

struct Edge {
    int u, v, val, id;
    int x, y;

    Edge() {}
    Edge(int U, int V, int Val) : u(U), v(V), val(Val) {}

    bool operator<(const Edge &o) const { return val < o.val; }
} e[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].val;
        e[i].id = i;
    }
    sort(e + 1, e + 1 + m);
    e[0].val = -1;
    for (int i = 1; i <= m;) {
        int j = i;
        do {
            e[j].x = get(e[j].u);
            e[j].y = get(e[j].v);
            j++;
        } while (j <= m && e[j].val == e[j - 1].val);
        while (i < j) {
            while (get(e[i].u) == get(e[i].v) && i < j) i++;
            if (i < j) merge(e[i].u, e[i].v);
        }
    }
    cin >> q;
    sort(e + 1, e + 1 + m, [](Edge a, Edge b) -> bool { return a.id < b.id; });
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    while (q --> 0) {
        static int k;
        vector<Edge> v;
        cin >> k;
        for (int i = 1, a; i <= k; i++) {
            cin >> a;
            v.emplace_back(e[a].x, e[a].y, e[a].val);
        }
        sort(v.begin(), v.end());
        bool flag = true;
        for (int i = 0; i < v.size() && flag;) {
            if (get(v[i].u) == get(v[i].v)) {
                flag = false;
                break;
            }
            merge(v[i].u, v[i].v);
            int j = i + 1;
            while (j < v.size() && v[j].val == v[i].val) {
                if (get(v[j].u) == get(v[j].v)) {
                    flag = false;
                    break;
                }
                merge(v[j].u, v[j].v);
                j++;
            }
            while (i < j) fa[v[i].u] = v[i].u, fa[v[i].v] = v[i].v, i++;
        }
        cout << (flag ? "YES\n" : "NO\n");
    }

    return 0;
}