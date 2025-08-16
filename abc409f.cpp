#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 3010;
int n, q, cnt, x[MAXN], y[MAXN], fa[MAXN];

int get(int x) {
    while (fa[x] ^ x) x = fa[x];
    return x;
}

void merge(int x, int y) { fa[get(x)] = fa[get(y)]; }

struct Edge
{
    int u, v, w;
    Edge() {}
    Edge(int U, int V, int W) : u(U), v(V), w(W) {}

    bool operator<(const Edge &o) const { return w > o.w; }
};
priority_queue<Edge> pq;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n + q; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        for (int j = 1; j < i; j++)
            pq.emplace(i, j, abs(x[i] - x[j]) + abs(y[i] - y[j]));
    }
    cnt = n;

    while (q --> 0) {
        static int op, u, v;
        cin >> op;
        if (op == 1) {
            cin >> x[n + 1] >> y[n + 1];
            n++, cnt++;
            for (int i = 1; i < n; i++)
                pq.emplace(i, n, abs(x[i] - x[n]) + abs(y[i] - y[n]));
        } else if (op == 2) {
            if (cnt == 1) {
                cout << -1 << '\n';
                continue;
            }
            while (!pq.empty() && get(pq.top().u) == get(pq.top().v)) pq.pop();
            int k = pq.top().w;
            while (!pq.empty() && pq.top().w == k) {
                auto [u, v, w] = pq.top(); pq.pop();
                cnt -= bool(get(u) ^ get(v));
                merge(u, v);
            }
            cout << k << '\n';
        } else {
            cin >> u >> v;
            cout << (get(u) == get(v) ? "Yes\n" : "No\n");
        }
    }

    return 0;
}