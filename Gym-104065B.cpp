#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 4e5 + 10, S = 600;
int n, cnt, sum[MAXN];
queue<int> q;
bitset<MAXN> del, vis;

struct Interval {
    int l, r, k;
} a[MAXN];

struct Node {
    int l, r;
    vector<int> v;
} t[MAXN << 2];

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return;

    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
}

void Insert(int p, int l, int r, int id) {
    if (l <= t[p].l && t[p].r <= r) return t[p].v.emplace_back(id), void();

    if (l <= t[p << 1].r) Insert(p << 1, l, r, id);
    if (r >= t[p << 1 | 1].l) Insert(p << 1 | 1, l, r, id);
}

void Remove(int p) {
    static vector<int> v;
    v.clear();
    for (auto i : t[p].v) {
        if (a[i].k) {
            a[i].k--;
            if (a[i].k) v.emplace_back(i);
            else q.emplace(i);
        }
    }
    swap(t[p].v, v);
}

void Remove(int p, int pos) {
    Remove(p);
    if (t[p].l == t[p].r) return;
    if (pos <= t[p << 1].r) Remove(p << 1, pos);
    else Remove(p << 1 | 1, pos);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    build(1, 1, n);
    for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r >> a[i].k;

    for (int i = 1; i <= n; i++) if (!a[i].k) q.emplace(i), vis[i] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (cnt % S == 0) {
            for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + del[i];
            for (int i = 1; i <= n; i++) {
                if (!vis[i] && sum[a[i].r] - sum[a[i].l - 1] + S >= a[i].k) {
                    a[i].k -= sum[a[i].r] - sum[a[i].l - 1];
                    Insert(1, a[i].l, a[i].r, i);
                    vis[i] = 1;
                }
            }
        }
        cnt++;
        Remove(1, x);
        del[x] = 1;
    }
    cout << cnt << '\n';

    return 0;
}