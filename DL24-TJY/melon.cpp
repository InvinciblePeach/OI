#include <bits/stdc++.h>

using namespace std;

const int H = 20, W = 10;
int n, g[H + 5][W + 5], mn[W + 5];

void out(int k, int h, int l) {
    cerr << k << ":" << h << ' ' << l << "\n";
    for (int x = 1; x <= H; x++) {
        for (int y = 1; y <= W; y++) cerr << g[x][y] << " \n"[y == W];
    }
    for (int i = 1; i <= W; i++) cerr << mn[i] << ":\n"[i == W];
    for (int i = 1; i <= W; i++) assert(!g[mn[i] - 1][i]);
    // cerr << '\n';
}

signed main() {
    freopen("melon.in", "r", stdin);
    freopen("melon.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= W; i++) mn[i] = H + 1;
    for (int i = 1, h, l; i <= n; i++) {
        cin >> h >> l;
        g[--mn[h]][h] = l;
        
        bool flag = false;
        do {
            flag = false;
            for (int y = 1; y <= W; y++) {
                for (int x = H; x; x--) {
                    if (g[x][y] && g[x][y] == g[x - 1][y]) {
                        g[x][y]++, g[x - 1][y] = 0;
                        for (int k = x - 1; k >= mn[y]; k--) g[k][y] = g[k - 1][y];
                        mn[y]++;
                        flag = true;
                        break;
                    }
                }
            }
            if (!flag) {
                for (int y = 1; y <= W; y++) {
                    for (int x = H; x; x--) {
                        if (g[x][y] && g[x][y] == g[x][y + 1]) {
                            g[x][y]++, g[x][y + 1] = 0;
                            for (int k = x; k >= mn[y + 1]; k--) g[k][y + 1] = g[k - 1][y + 1];
                            mn[y + 1]++;
                            flag = true;
                            break;
                        }
                    }
                }
            }
        } while (flag);
        // if (200 <= i && i <= 250) out(i, h, l);
    }
    for (int x = 1; x <= H; x++) {
        for (int y = 1; y <= W; y++) cout << g[x][y] << " \n"[y == W];
    }
    return 0;
}