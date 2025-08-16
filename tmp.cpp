#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
map<int, int> mp;
int mcnt;
struct Node {
    int x, y, t, v, id;
} q[1500005];
bool cmpByT(const Node &a, const Node &b) { return a.t != b.t ? a.t < b.t : a.id < b.id; }
bool cmpByX(const Node &a, const Node &b) { return a.x != b.x ? a.x < b.x : a.id < b.id; }
int qcnt;
int pre[200005];
struct ODTNode {
    int l, r, v;
    bool operator<(const ODTNode &o) const { return l < o.l; }
};
struct ODT {
    typedef set<ODTNode>::iterator iter;
    set<ODTNode> tr, col[200005];
    iter Insert(int l, int r, int v) {
        col[v].insert({l, r, v});
        return tr.insert({l, r, v}).first;
    }
    void Delete(int l, int r, int v) {
        col[v].erase({l, r, v});
        tr.erase({l, r, v});
    }
    iter Split(int p) {
        iter it = tr.lower_bound({p, 0, 0});
        if (it != tr.end() && it->l == p) return it;
        it--;
        int l = it->l, r = it->r, v = it->v;
        Delete(l, r, v);
        Insert(l, p - 1, v);
        return Insert(p, r, v);
    }
    int Pre(int p) {
        iter it = --tr.upper_bound({p, 0, 0});
        if (it->l < p)
            return p - 1;
        else {
            iter co = col[it->v].lower_bound({p, 0, 0});
            if (co != col[it->v].begin()) return (--co)->r;
            return 0;
        }
    }
    void Assign(int l, int r, int v, int t) {
        iter itr = Split(r + 1), itl = Split(l);
        vector<int> ps;
        for (iter it = itl; it != itr; it++) {
            if (it != itl) ps.emplace_back(it->l);
            iter nxt = col[it->v].upper_bound(*it);
            if (nxt != col[it->v].end()) ps.emplace_back(nxt->l);
            col[it->v].erase(*it);
        }
        tr.erase(itl, itr);
        Insert(l, r, v);
        ps.emplace_back(l);
        iter nxt = col[v].upper_bound({l, r, v});
        if (nxt != col[v].end()) ps.emplace_back(nxt->l);
        for (int i = 0; i < ps.size(); i++) {
            q[++qcnt] = {ps[i], pre[ps[i]], t, -1, 0};
            pre[ps[i]] = Pre(ps[i]);
            q[++qcnt] = {ps[i], pre[ps[i]], t, 1, 0};
        }
    }
} odt;
struct BIT {
    int f[100005];
    BIT() { memset(f, 0, sizeof(f)); }
    int lowbit(int x) { return x & -x; }
    void Modify(int i, int x) {
        for (; i <= 100001; i += lowbit(i)) f[i] += x;
    }
    int Query(int i) {
        int res = 0;
        for (; i; i -= lowbit(i)) res += f[i];
        return res;
    }
} bit;
int a[100005], las[200005];
int ans[100005], acnt;
void CDQ(int l, int r) {
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    int i = l, j = mid + 1;
    while (j <= r) {
        while (i <= mid && q[i].x <= q[j].x) {
            if (!q[i].id) bit.Modify(q[i].y + 1, q[i].v);
            i++;
        }
        if (q[j].id) ans[q[j].id] += bit.Query(q[j].y + 1) * q[j].v;
        j++;
    }
    for (int k = l; k < i; k++)
        if (!q[k].id) bit.Modify(q[k].y + 1, -q[k].v);
    inplace_merge(q + l, q + mid + 1, q + r + 1, cmpByX);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (!mp[a[i]]) mp[a[i]] = ++mcnt;
        a[i] = mp[a[i]];
        pre[i] = las[a[i]];
        las[a[i]] = i;
        q[++qcnt] = {i, pre[i], 0, 1, 0};
        odt.Insert(i, i, a[i]);
    }
    for (int i = 1; i <= m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r, v;
            scanf("%d%d%d", &l, &r, &v);
            if (!mp[v]) mp[v] = ++mcnt;
            v = mp[v];
            odt.Assign(l, r, v, i);
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            q[++qcnt] = {r, l - 1, i, 1, ++acnt};
            q[++qcnt] = {l - 1, l - 1, i, -1, acnt};
        }
    }
    sort(q + 1, q + qcnt + 1, cmpByT);
    CDQ(1, qcnt);
    for (int i = 1; i <= acnt; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
