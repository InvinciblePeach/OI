#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int MAXN = 1e5 + 10, mod = 1e6;
int n, m, k, fa[MAXN], sum, cnt;
bitset<MAXN> use;
struct Edge {
    int u, v, w, c, id;

    bool operator<(const Edge &o) const { return w == o.w ? c < o.c : w < o.w; }
} e[MAXN];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

void merge(int x, int y) { fa[get(x)] = get(y); }

void kruskal() {
    sort(e + 1, e + 1 + m);
    sum = cnt = 0;
    use.reset();
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1, j = 1; i < n; i++) {
        while (get(e[j].u) == get(e[j].v))
            j++;
        merge(e[j].u, e[j].v);
        use[j] = 1;
        if (!e[j].c) cnt++;
        sum += e[j].w;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].c;
        e[i].w = rnd() % mod, e[i].id = i;
    }
    int l = -mod, r = mod;
    while (l <= r) {
        int mid = (l + r) >> 1;
        for (int i = 1; i <= m; i++)
            if (!e[i].c) e[i].w += mid;
        kruskal();
        if (cnt == k) break;
        if (cnt > k)
            l = mid + 1;
        else
            r = mid - 1;
        for (int i = 1; i <= m; i++)
            if (!e[i].c) e[i].w -= mid;
    }
    if (cnt ^ k) {
        cout << "no solution\n";
        return 0;
    } else {
        for (int i = 1; i <= m; i++) {
            if (use[i]) cout << e[i].u << ' ' << e[i].v << ' ' << e[i].c << '\n';
        }
    }

    return 0;
}