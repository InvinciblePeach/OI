#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int MAXN = 2e6 + 10;
int n, tot = 1, son[MAXN][26], k[MAXN], ans[MAXN];
vector<int> id[MAXN];
string s;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> st[MAXN];

void dfs(int u) {
    for (int i = 0; i < 26; i++) {
        if (!son[u][i]) continue;
        dfs(son[u][i]);
        if (st[u].size() < st[son[u][i]].size()) swap(st[u], st[son[u][i]]);
        for (auto p : st[son[u][i]]) st[u].insert(p);
    }
    for (auto p : id[u]) {
        if (k[p] <= st[u].size())
            ans[p] = *st[u].find_by_order(k[p] - 1);
        else
            ans[p] = -1;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1, rt; i <= n; i++) {
        cin >> s;
        reverse(s.begin(), s.end());
        rt = 1;
        for (auto c : s) {
            if (!son[rt][c - 'a']) son[rt][c - 'a'] = ++tot;
            rt = son[rt][c - 'a'];
        }
        id[rt].emplace_back(i);
        st[rt].insert(i);
    }
    for (int i = 1; i <= n; i++) cin >> k[i];
    dfs(1);
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
    return 0;
}