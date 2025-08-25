#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 60, MAXM = 2e5 + 10;
int T, ans, fa[MAXN], d[MAXN];
bitset<MAXN> vis;
string s, t;

constexpr int change(char c) { return (c < 'a' ? c - 'A' + 1 : c - 'a' + 27); }

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    if (fa[u]) dfs(fa[u]);
}

void solve() {
    cin >> s >> t;
    vis.reset(), ans = 0;
    memset(fa, 0, sizeof(fa));
    memset(d, 0, sizeof(d));
    for (int i = 0; i < s.size(); i++) {
        int a = change(s[i]), b = change(t[i]);
        if (fa[a] && fa[a] != b) {
            cout << "-1\n";
            return;
        }
        fa[a] = b;
    }

    for (int i = 1; i <= 52; i++) {
        if (fa[i]) {
            ans += (fa[i] != i);
            d[fa[i]]++;
        }
    }

    bool flag = false;

    for (int i = 1; i <= 52; i++)
        if (!fa[i] || !d[i]) flag = true;
    
    for (int i = 1; i <= 52; i++) {
        if (!d[i] || fa[i] == i) dfs(i);
    }

    for (int i = 1; i <= 52; i++) {
        if (!vis[i]) {
            ans++;
            dfs(i);
            if (!flag) {
                cout << "-1\n";
                return;
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) solve();

    return 0;
}