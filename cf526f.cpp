#include <bits/stdc++.h>
#define int long long
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 5e5 + 10;
int n, ans, top1, top2;
pii pnt[MAXN], st1[MAXN], st2[MAXN];

struct Node {
    int l, r;
    int mn, tag, cnt;
} t[MAXN << 2];

void pushup(int p) {
    t[p].mn = min(t[lc(p)].mn, t[rc(p)].mn);
    t[p].cnt = (t[lc(p)].mn == t[p].mn ? t[lc(p)].cnt : 0) + (t[rc(p)].mn == t[p].mn ? t[rc(p)].cnt : 0);
}

void pushdown(int p) {
    int &tag = t[p].tag;
    t[lc(p)].mn += tag, t[rc(p)].mn += tag;
    t[lc(p)].tag += tag, t[rc(p)].tag += tag;
    tag = 0;
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return t[p].mn = l, t[p].cnt = 1, void();
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r) return t[p].mn += val, t[p].tag += val, void();

    pushdown(p);
    if (l <= t[lc(p)].r) modify(lc(p), l, r, val);
    if (r >= t[rc(p)].l) modify(rc(p), l, r, val);
    pushup(p);
}

int query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].mn ? 0 : t[p].cnt;

    pushdown(p);
    int res = 0;
    if (l <= t[lc(p)].r) res += query(lc(p), l, r);
    if (r >= t[rc(p)].l) res += query(rc(p), l, r);
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> pnt[i].first >> pnt[i].second;
    sort(pnt + 1, pnt + 1 + n);
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        modify(1, 1, n, -1);
        while (top1 && st1[top1].second < pnt[i].second)
            modify(1, st1[top1 - 1].first + 1, st1[top1].first, pnt[i].second - st1[top1].second), --top1;
        st1[++top1] = {i, pnt[i].second};
        while (top2 && st2[top2].second > pnt[i].second)
            modify(1, st2[top2 - 1].first + 1, st2[top2].first, st2[top2].second - pnt[i].second), --top2;
        st2[++top2] = {i, pnt[i].second};
        ans += query(1, 1, i);
    }
    cout << ans << '\n';

    return 0;
}