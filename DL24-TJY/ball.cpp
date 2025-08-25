#include <bits/stdc++.h>
#define int long long

using namespace std;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10;
int n, k, v, res, ans, p1[15], p2[15], v1, v2, x[MAXN][15], cnt[MAXN];
pii dis1[MAXN], dis2[MAXN];

constexpr int pw2(int x) { return x * x; }

int calc(int *x, int *p) {
    int sum = 0;
    for (int i = 1; i <= k; i++) sum += pw2(x[i] - p[i]);
    return sum;
}

void add(int x) {
    if (!cnt[x]++) res++;
}

void del(int x) {
    if (!--cnt[x]) res--;
}

signed main() {
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k >> v >> v1 >> v2;
    for (int i = 1; i <= k; i++) cin >> p1[i];
    for (int i = 1; i <= k; i++) cin >> p2[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) cin >> x[i][j];
        dis1[i] = {calc(x[i], p1), i};
        dis2[i] = {calc(x[i], p2), i};
    }
    sort(dis1 + 1, dis1 + 1 + n);
    sort(dis2 + 1, dis2 + 1 + n);
    int l = 0, r = n;
    for (int i = 1; i <= n; i++) add(dis2[i].second);
    for (; l <= n; add(dis1[++l].second)) {
        while (r && v1 * dis1[l].first + v2 * dis2[r].first > v) del(dis2[r--].second);
        if (l <= 5) cerr << l << ' ' << r << '\n';
        if (v1 * dis1[l].first + v2 * dis2[r].first <= v) ans = max(ans, res);
    }
    cout << ans << '\n';
    
    return 0;
}