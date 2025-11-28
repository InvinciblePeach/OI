#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10;
int n, tot, t[MAXN][26], nxt[MAXN], deg[MAXN], cnt[MAXN], ans[MAXN];
vector<int> ed[MAXN];

void insert(const string &s, int id) {
    int rt = 0;
    for (auto c : s) {
        if (!t[rt][c - 'a']) t[rt][c - 'a'] = ++tot;
        rt = t[rt][c - 'a'];
    }
    ed[rt].emplace_back(id);
}

void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (t[0][i]) q.emplace(t[0][i]);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            auto &v = t[u][i];
            if (!v) {
                v = t[nxt[u]][i];
                continue;
            }
            nxt[v] = t[nxt[u]][i];
            deg[nxt[v]]++;
            q.emplace(v);
        }
    }
}

void query(const string &s) {
    int rt = 0;
    for (auto c : s) {
        rt = t[rt][c - 'a'];
        cnt[rt]++;
    }
}

void topu() {
    queue<int> q;
    for (int i = 0; i <= tot; i++)
        if (!deg[i]) q.emplace(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto x : ed[u]) ans[x] += cnt[u];
        cnt[nxt[u]] += cnt[u];
        if (!--deg[nxt[u]]) q.emplace(nxt[u]);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    string s;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        insert(s, i);
    }
    build();
    cin >> s;
    query(s);
    topu();
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';

    return 0;
}