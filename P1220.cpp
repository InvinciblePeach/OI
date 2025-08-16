#include <bits/stdc++.h>

using namespace std;

int n, c, s, sum;
int min_ = INT_MAX, max_ = INT_MIN, ans = INT_MAX;
unordered_map<int, int> lights;

void dfs(int i, int all, int cnt, int cos) {
    all -= lights[i];
    lights[i] = 0;
    if (cnt == n) { ans = min(ans, cos); return; }
    else if (cos >= ans) { return; }

    int l = i - 1;
    while (!lights[l] && l >= min_) { l --; }
    if (l >= min_) {
        int tmp = lights[l];
        dfs(l, all, cnt + 1, cos + all * (i - l));
        lights[l] = tmp;
    }

    int r = i + 1;
    while (!lights[r] && r <= max_) { r ++; }
    if (r <= max_) {
        int tmp = lights[r];
        dfs(r, all, cnt + 1, cos + all * (r - i));
        lights[r] = tmp;
    }
}

int main() {
    cin >> n >> c;

    for (int i = 1; i <= n; i ++) {
        int m, w;
        cin >> m >> w;
        lights[m] = w;
        sum += w;
        min_ = min(m, min_);
        max_ = max(m, max_);
        if (i == c) { s = m; }
    }

    dfs(s, sum, 1, 0);

    cout << ans << endl;

    return 0;
}