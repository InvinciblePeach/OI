#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10;
int n, a[MAXN], cnt1[MAXN], cnt2[MAXN], sg[MAXN][2];
vector<int> g[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cnt1[cin >> a[i], a[i]]++;
    for (int i = 2; i < MAXN; i++) {
        for (int j = i; j < MAXN; j += i) {
            g[j].emplace_back(i);
            if (i < j) cnt1[i] += cnt1[j];
        }
    }
    for (int i = 2; i < MAXN; i++) {
        bool flag = false;
        for (auto v : g[i]) cnt2[v] = cnt1[v];
        for (int j = g[i].size() - 1; ~j; j--) {
            auto v = g[i][j];
            if (j < g[i].size() - 1 && cnt2[v]) {
                if (!sg[v][1]) sg[i][0] = flag = true;
                if (!sg[v][0]) sg[i][1] = flag = true;
            }
            for (auto w : g[v]) cnt2[w] -= cnt2[v];
        }
        if (!flag) sg[i][cnt1[i] & 1] = true;
    }
    for (int i = 1; i <= n; i++) cout << (sg[a[i]][0] ? "Aoki\n" : "Takahashi\n");

    return 0;
}