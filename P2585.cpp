#include <bits/stdc++.h>

using namespace std;

string s;
int p;
int f[500005][3], g[500005][3]; /* 0 : green, 1 : red, 2 : blue */

void dfs(int now_p) {
    if (s[now_p] == '0') {
        f[now_p][0] = g[now_p][0] = 1;
        f[now_p][1] = f[now_p][2] = g[now_p][1] = g[now_p][2] = 0;
        return;
    }

    dfs(++ P);

    if (s[now_p] == '1') {
        f[now_p][0] = max(f[now_p + 1][1], f[now_p + 1][2]) + 1;
        f[now_p][1] = max(f[now_p + 1][0], f[now_p + 1][2]);
        f[now_p][2] = max(f[now_p + 1][0], f[now_p + 1][1]);

        g[now_p][0] = min(g[now_p + 1][1], g[now_p + 1][2]) + 1;
        g[now_p][1] = min(g[now_p + 1][0], g[now_p + 1][2]);
        g[now_p][2] = min(g[now_p + 1][0], g[now_p + 1][1]);
    } else {
        int tmp = ++P;
        dfs(tmp);

        f[now_p][0] = max(f[now_p + 1][1] + f[tmp][2], f[now_p + 1][2] + f[tmp][1]) + 1;
        f[now_p][1] = max(f[now_p + 1][0] + f[tmp][2], f[now_p + 1][2] + f[tmp][0]);
        f[now_p][2] = max(f[now_p + 1][0] + f[tmp][1], f[now_p + 1][1] + f[tmp][0]);

        g[now_p][0] = min(g[now_p + 1][1] + g[tmp][2], g[now_p + 1][2] + g[tmp][1]) + 1;
        g[now_p][1] = min(g[now_p + 1][0] + g[tmp][2], g[now_p + 1][2] + g[tmp][0]);
        g[now_p][2] = min(g[now_p + 1][0] + g[tmp][1], g[now_p + 1][1] + g[tmp][0]);
    }
}

int main() {
    cin >> s;

    dfs(P);

    cout << max({f[0][0], f[0][1], f[0][2]}) << ' ' << min({g[0][0], g[0][1], g[0][2]}) << endl;
    return 0;
}