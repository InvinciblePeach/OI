#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

ull n, w, a[1000005], ans = 0;
set<ull> f;

bool dfs_fd(ull i, ull j) {
    if (j > w) {
        return false;
    }
    if (i > (1 + n) / 2) {
        f.emplace(j);
        return true;
    }

    dfs_fd(i + 1, j);
    dfs_fd(i + 1, j + a[i]);
    return false;
}

bool dfs_bk(ull i, ull j) {
    if (j > w) {
        return false;
    }
    if (i > n) {
        auto A = f.upper_bound(w - j);
        A --;
        ans = max(ans, j + * A);
        return true;
    }

    dfs_bk(i + 1, j);
    dfs_bk(i + 1, j + a[i]);
    return false;
}

int main() {
    cin >> n;
    for (ull i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> w;

    w = * (upper_bound(a + 1, a + 1 + n, w) - 1);

    sort(a + 1, a + 1 + n, greater<>());

    dfs_fd(1, 0);
    dfs_bk(1 + n / 2, 0);

    cout << ans << endl;
    return 0;
}
