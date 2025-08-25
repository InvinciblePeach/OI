#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, m, k, top, fa[MAXN], siz[MAXN], st[MAXN];

int get(int x) {
    while (x ^ fa[x]) x = fa[x];
    return x;
}

void merge(int x, int y) {
    int fax = get(x), fay = get(y);
    if (fax == fay) return;
    if (siz[fax] > siz[fay]) swap(fax, fay);
    fa[fax] = fay, st[++top] = fax, siz[fay] += siz[fax];
}

void back() { siz[fa[st[top]]] -= siz[st[top]], fa[st[top]] = st[top], top--; }

struct Edge {
    int u, v;
    Edge() {}
    Edge(int U, int V) : u(U), v(V) {}
};

struct Node {
    int l, r;
    vector<Edge> v;
} t[MAXN << 2];

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return;

    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
}

void modify(int p, int l, int r, const Edge &e) {
    if (l <= t[p].l && t[p].r <= r) return t[p].v.emplace_back(e), void();
    
    if (l <= t[lc(p)].r) modify(lc(p), l, r, e);
    if (r >= t[rc(p)].l) modify(rc(p), l, r, e);
}

void dfs(int p) {
    bool flag = true;
    int tmp = top;
    for (auto [u, v] : t[p].v) {
        if (get(u) == get(v)) {
            for (int i = t[p].l; i <= t[p].r; i++) cout << "No\n";
            flag = false;
            break;
        }
        merge(u, v + n), merge(u + n, v);
    }
    if (flag) {
        if (t[p].l == t[p].r) cout << "Yes\n";
        else dfs(lc(p)), dfs(rc(p));
    }
    while (top > tmp) back();
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    build(1, 1, k);
    for (int i = 1, x, y, l, r; i <= m; i++) {
        cin >> x >> y >> l >> r;
        if (l ^ r) modify(1, l + 1, r, {x, y});
    }
    for (int i = 1; i <= (n << 1); i++) fa[i] = i, siz[i] = 1;
    dfs(1);

    return 0;
}