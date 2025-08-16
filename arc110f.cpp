#include <bits/stdc++.h>

using namespace std;

int n;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    cout << n * n << '\n';
    for (int i = n - 1; ~i; i--)
        for (int j = 1; j <= n; j++)
            cout << i << '\n';
    return 0;
}