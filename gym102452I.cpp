#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 10;
int n, m, lst, tot, y[MAXN], tag[MAXN], vis[MAXN];
vector<int> pos[MAXN], ans;

struct Node {
    int val, id, t;

    Node() {}
    Node(const int &Val, const int &Id, const int &T)
        : val(Val), id(Id), t(T) {}

    bool operator<(const Node &o) const { return val > o.val; }
};
priority_queue<Node> q[MAXN];

void brute(int i, int t) {
    if (vis[i])
        for (auto p : pos[i])
            y[i] -= tag[p];
    int d = (max(0, y[i]) + pos[i].size() - 1) / pos[i].size();
    if (!d) {
        ans.emplace_back(i), vis[i] = -1;
        return;
    }
    for (auto p : pos[i]) {
        q[p].emplace(d + tag[p], i, t);
        y[i] += tag[p];
    }
    vis[i] = t;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int time = 1; time <= m; time++) {
        int op, x, k;
        cin >> op;
        if (op == 2) {
            cin >> x >> k;
            x ^= lst, k ^= lst;
            tag[x] += k;
            while (!q[x].empty() && q[x].top().val <= tag[x]) {
                int val = q[x].top().val, id = q[x].top().id, t = q[x].top().t;
                if (vis[id] == t) brute(id, time);
                q[x].pop();
            }
            sort(ans.begin(), ans.end());
            cout << (lst = ans.size());
            for (auto i : ans)
                cout << ' ' << i;
            cout << '\n';
            ans.clear();
        } else if (op == 1) {
            cin >> y[++tot] >> k;
            y[tot] ^= lst;
            for (int i = 1, p; i <= k; i++) {
                cin >> p;
                pos[tot].emplace_back(p ^ lst);
            }
            brute(tot, time);
        }
    }

    return 0;
}