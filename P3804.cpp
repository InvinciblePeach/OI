#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n, ans;
string s;

namespace sam {
    int tot = 1, lst = 1, siz[MAXN];
    vector<int> g[MAXN];
    struct Node {
        int len, nxt;
        int v[26];
    } st[MAXN << 1];

    void add(int c) {
        int p = lst, np = lst = ++tot;
        siz[tot] = 1;
        st[np].len = st[p].len + 1;
        for (; p && !st[p].v[c]; p = st[p].nxt) st[p].v[c] = np;
        if (!p)
            st[np].nxt = 1;
        else {
            int q = st[p].v[c];
            if (st[q].len = st[p].len + 1)
                st[np].nxt = q;
            else {
                int nq = ++tot;
                st[nq] = st[q];
                st[nq].len = st[p].len + 1;
                for (; p && st[p].v[c] == q; p = st[p].nxt) st[p].v[c] = nq;
            }
        }
    }

    void dfs(int u) {
        for (auto v : g[u]) {
            dfs(v);
            siz[u] += siz[v];
        }
        if (siz[u] != 1) ans = max(ans, siz[u] * st[u].len);
    }

    void solve() {
        for (int i = 2; i <= tot; i++) g[st[i].nxt].emplace_back(i);
        dfs(1);
    }
} // namespace sam

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) sam::add(s[i] - 'a');
    sam::solve();
    cout << ans << '\n';

    return 0;
}