#include <bits/stdc++.h>
#define lc first
#define rc second

using namespace std;

int n, ans = 1;
int v[1000005];
pair<int, int> tree[1000005]; // NOLINT
bool flag;

int dfs(int l, int r, int cnt) {
    if (l == -1 && r == -1) { return 0; }
    if (l == -1 || r == -1) { flag = true; return 0; }
    if (v[l] != v[r]) { flag = true; return 0; }

    return dfs(tree[l].lc, tree[r].rc, 2) + dfs(tree[l].rc, tree[r].lc, 2) + cnt;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> v[i];
    }

    for (int i = 1; i <= n; i ++) {
        int l, r;
        cin >> l >> r;
        tree[i].lc = l, tree[i].rc = r;
    }

    for (int i = 1; i <= n; i ++) {
        int tmp = dfs(tree[i].lc, tree[i].rc, 3);
        if (!flag) { ans = max(ans, tmp); }
        flag = false;
    }

    cout << ans << endl;

    return 0;
}