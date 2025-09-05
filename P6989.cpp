#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 110;
int n, v[MAXN][3], g[MAXN][3], t[MAXN * MAXN][3], vis[MAXN * MAXN][MAXN];
char val[]{'R', 'P', 'S'}, w[MAXN], ans[MAXN * MAXN];
map<char, int> mp{{'R', 0}, {'P', 1}, {'S', 2}};

int tot;
void cpy() {
    for (int i = 1; i <= n; i++) {
        ans[tot + i] = ans[i];
        for (int j = 0; j < 3; j++)
            if (g[i][j]) t[tot + i][j] = g[i][j] + tot;
    }
    tot += n;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i][0] >> v[i][1] >> v[i][2];
        ans[i] = val[(mp[w[i]] + 1) % 3];
        g[i][mp[w[i]]] = v[i][mp[ans[i]]];
    }
    cpy();
    for (int i = 2; i <= n; i++) {
        static int tim;
        tim++;
        int x = 1, y = i;
        while (true) {
            if (vis[x][y] == tim) break;
            vis[x][y] = tim;
            if (!t[x][mp[w[y]]]) {
                cpy();
                t[x][mp[w[y]]] = tot - n + v[y][mp[ans[x]]];
            }
            auto tmp = x;
            x = t[x][mp[w[y]]];
            y = v[y][mp[ans[tmp]]];
        }
    }
    cout << tot << '\n';
    for (int i = 1; i <= tot; i++) {
        cout << ans[i] << ' ';
        for (int j = 0; j < 3; j++) cout << (t[i][j] ? t[i][j] : 1) << " \n"[j == 2];
    }
    return 0;
}