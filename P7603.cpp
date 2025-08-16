#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 10;
int n, m, tot, X[MAXN], vis[MAXN];
ll Y[MAXN], mnp[MAXN], tag[MAXN], lst;
vector<int> pos[MAXN], ans;

struct Node {
    ll val;
    int id, t;

    Node() {}
    Node(const ll &Val, const int &Id, const int &T)
        : val(Val), id(Id), t(T) {}

    bool operator<(const Node &o) const { return val > o.val; }
};
priority_queue<Node> q[MAXN];

void brute(int i, int t) {
    int x = X[i];
    if (vis[i])
        for (auto p : pos[x])
            Y[i] -= tag[p];
    int d = (max(0ll, Y[i]) + pos[x].size() - 1) / pos[x].size();
    if (!d) {
        ans.emplace_back(i), vis[i] = -1;
        return;
    }
    for (auto p : pos[x]) {
        q[p].emplace(d + tag[p], i, t);
        Y[i] += tag[p];
    }
    vis[i] = t;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        mnp[i] = i;
        for (int j = 2; j * j <= i; j++)
            if (i % j == 0) {
                mnp[i] = j;
                break;
            }
    }
    for (int i = 1; i <= n; i++) {
        int t = i;
        while (t > 1)
            pos[i].emplace_back(mnp[t]), t /= mnp[t];
        pos[i].resize(unique(pos[i].begin(), pos[i].end()) - pos[i].begin());
    }

    for (int time = 1; time <= m; time++) {
        int op, x;
        uint y;
        cin >> op >> x >> y;
        y ^= lst;
        if (op == 0) {
            for (auto p : pos[x]) tag[p] += y;
            for (auto p : pos[x]) {
                while (!q[p].empty() && q[p].top().val <= tag[p]) {
                    auto [val, id, t] = q[p].top();
                    if (vis[id] == t) brute(id, time);
                    q[p].pop();
                }
            }
            sort(ans.begin(), ans.end());
            cout << (lst = ans.size()) << ' ';
            for (auto i : ans)
                cout << i << ' ';
            cout << '\n';
            ans.clear();
        } else if (op == 1) ++tot, Y[tot] = y, X[tot] = x, brute(tot, time);
    }

    return 0;
}