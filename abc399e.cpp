#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 30, MAXM = 2e5 + 10;
int n, m, ans, fa[MAXN], d[MAXN];
bool flag;
bitset<MAXN> vis;
string s, t;

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    if (fa[u]) dfs(fa[u]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> s >> t;
    for (int i = 0; i < n; i++) {
        int a = s[i] - 'a' + 1, b = t[i] - 'a' + 1;
        cerr << a << ' ' << b << ' ';
        if (fa[a] && fa[a] != b) {
            cout << "-1\n";
            return 0;
        }
        fa[a] = b;
    }

    for (int i = 1; i <= 26; i++) {
        if (fa[i]) {
            ans += (fa[i] != i);
            d[fa[i]]++;
        }
    }

    for (int i = 1; i <= 26; i++)
        if (!fa[i] || !d[i]) flag = true;
    
    for (int i = 1; i <= 26; i++) {
        if (!d[i] || fa[i] == i) dfs(i);
    }

    for (int i = 1; i <= 26; i++) {
        if (!vis[i]) {
            ans++;
            dfs(i);
            if (!flag) {
                cout << "-1\n";
                return 0;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}