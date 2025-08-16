#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10, S = 320;
int n, m, a[MAXN], q[MAXN], ans[MAXN];
int bl[MAXN], L[S], R[S];
priority_queue<int> P[S], Q[S];

struct Query {
    int l, r, id;

    bool operator<(const Query &o) const { return r < o.r; }
} qry[MAXN];

struct Fenwick {
    int t[MAXN];

    constexpr int lowbit(const int &x) { return x & -x; }

    void add(int x, int val) {
        for (x++; x <= n + 1; x += lowbit(x)) t[x] += val;
    }

    int query(int x) {
        int res = 0;
        for (x++; x; x -= lowbit(x)) res += t[x];
        return res;
    }
} T;

void rebuild(int b) {
    auto &que = Q[b];
    if (que.empty()) return;
    for (int i = L[b]; i <= R[b]; i++) {
        if (q[i] > -que.top()) {
            int tmp = -que.top();
            que.pop(), que.emplace(-q[i]), q[i] = tmp;
        }
    }
    priority_queue<int>().swap(que);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++)
        cin >> qry[i].l >> qry[i].r, qry[i].id = i;
    sort(qry + 1, qry + 1 + m);

    memset(L, 0x7f, sizeof(L));
    for (int i = 1; i <= n; i++) bl[i] = (i - 1 + S) / S, L[bl[i]] = min(L[bl[i]], i), R[bl[i]] = max(R[bl[i]], i);
	for (int i = 1; i <= bl[n]; i++)
        for(int j = L[i]; j <= R[i]; j++)
            P[i].emplace(0);

    int k = 1;
    T.add(0, n);
    for (int i = 1; i <= n; i++) {
        int &val = a[i], nw = 0;

        if (val + 1 <= n) {
            int b = bl[val + 1];
            rebuild(b);
            for (int j = val + 1; j <= R[b]; j++)
                if (q[j] > nw) swap(nw, q[j]);
            priority_queue<int>().swap(P[b]);
            for (int j = L[b]; j <= R[b]; j++) P[b].emplace(q[j]);

            for (int j = b + 1; j <= bl[n]; j++) {
                if (P[j].top() > nw) {
                    int tmp = P[j].top();
                    P[j].pop(), P[j].emplace(nw), Q[j].emplace(-nw), nw = tmp;
                }
            }
            T.add(nw, -1), T.add(0, 1);
        }

        int b = bl[val];
        rebuild(b);
        T.add(q[val], -1), T.add(q[val] = i, 1);
        priority_queue<int>().swap(P[b]);
        for (int j = L[b]; j <= R[b]; j++) P[b].emplace(q[j]);

        for (; k <= m && qry[k].r <= i; k++)
            ans[qry[k].id] = T.query(i) - T.query(qry[k].l - 1);
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';

    return 0;
}