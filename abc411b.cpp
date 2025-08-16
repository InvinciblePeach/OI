#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n, d[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 2; i <= n; i++)
        cin >> d[i], d[i] += d[i - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n - i; j++)
            cout << abs(d[i] - d[i + j]) << " \n"[j == n - i];

    return 0;
}