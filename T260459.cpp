#include <bits/stdc++.h>
#define int unsigned

using namespace std;

int n, Q;
int a[8005], f[8005], ans[8005];
vector<tuple<int, int, int>> v;

signed main() {
    cin >> n >> Q;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        f[i] = f[i - 1] ^ a[i];
    }
    for (int i = 1; i <= Q; i ++) {
        int x, y;
        cin >> x >> y;
        v.emplace_back(x, y, i);
    }

    if (Q == 0) {
        return 0;
    }

    sort(v.begin(), v.end());

    auto index = 0;

    for (int i = 1; i <= get<0>(*(v.end() - 1)); i ++) {
        while (get<0>(v[index]) == i) {
            ans[get<2>(v[index])] = f[get<1>(v[index])];
            index++;
        }
        for (int j = 1; j <= n; j ++) {
            f[j] = f[j - 1] ^ f[j];
        }
    }

    for (int i = 1; i <= Q; i ++) {
        cout << ans[i] << endl;
    }

    return 0;
}