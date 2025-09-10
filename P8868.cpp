#include <bits/stdc++.h>
#define int unsigned long long
#define lc(p) (p) << 1
#define rc(p) (p) << 1 | 1

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2.5e5 + 10;
int n, m, a[MAXN], b[MAXN], ans[MAXN];

struct Query {
    int l, r, id;

    bool operator<(const Query &o) const { return r < o.r; }
} qry[MAXN];

struct Node {
    int l, r;
    int tagA, tagB, sumA, sumB, sum, sumh, taghAB, taghA, taghB, cnt;

    void entag(int vA, int vB) {
        sum += sumB * vA;
        sumA += (r - l + 1) * vA;
        tagA += vA;

        sum += sumA * vB;
        sumB += (r - l + 1) * vB;
        tagB += vB;
    }

    void entagh(int vA, int vB, int vAB, int c) {
        sumh += sum * c + sumA * vB + sumB * vA + vAB * (r - l + 1);
        cnt += c;
        taghA += tagA * c + vA;
        taghB += tagB * c + vB;
        taghAB += tagA * tagB * c + tagA * vB + tagB * vA + vAB;
    }
} t[MAXN << 2];

void pushup(int p) {
    t[p].sum = t[lc(p)].sum + t[rc(p)].sum;
    t[p].sumA = t[lc(p)].sumA + t[rc(p)].sumA;
    t[p].sumB = t[lc(p)].sumB + t[rc(p)].sumB;
    t[p].sumh = t[lc(p)].sumh + t[rc(p)].sumh;
}

void pushdown(int p) {
    auto &[l, r, tagA, tagB, sumA, sumB, sum, sumh, taghAB, taghA, taghB, cnt] = t[p];
    t[lc(p)].entagh(taghA, taghB, taghAB, cnt);
    t[rc(p)].entagh(taghA, taghB, taghAB, cnt);
    t[lc(p)].entag(tagA, tagB), t[rc(p)].entag(tagA, tagB);
    tagA = tagB = taghA = taghB = taghAB = cnt = 0;
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
}

void modify(int p, int l, int r, int vA, int vB) {
    if (l <= t[p].l && t[p].r <= r) return t[p].entag(vA, vB);
    pushdown(p);
    if (l <= t[lc(p)].r) modify(lc(p), l, r, vA, vB);
    if (r >= t[rc(p)].l) modify(rc(p), l, r, vA, vB);
    pushup(p);
}

int query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].sumh;
    pushdown(p);
    int res = 0;
    if (l <= t[lc(p)].r) res += query(lc(p), l, r);
    if (r >= t[rc(p)].l) res += query(rc(p), l, r);
    return res;
}

void update() { t[1].entagh(0, 0, 0, 1); }

int stA[MAXN], topA, stB[MAXN], topB;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> qry[i].l >> qry[i].r, qry[i].id = i;
    sort(qry + 1, qry + 1 + m);
    build(1, 1, n);
    for (int i = 1, j = 1; i <= n && j <= m; i++) {
        while (topA && a[stA[topA]] < a[i]) {
            modify(1, stA[topA - 1] + 1, stA[topA], -a[stA[topA]], 0);
            topA--;
        }
        modify(1, stA[topA] + 1, i, a[i], 0);
        stA[++topA] = i;
        while (topB && b[stB[topB]] < b[i]) {
            modify(1, stB[topB - 1] + 1, stB[topB], 0, -b[stB[topB]]);
            topB--;
        }
        modify(1, stB[topB] + 1, i, 0, b[i]);
        stB[++topB] = i;
        update();
        for (; j <= m && qry[j].r <= i; j++) ans[qry[j].id] = query(1, qry[j].l, qry[j].r);
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';

    return 0;
}