#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n;
bitset<MAXN> ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    if (n & 1) ans[(n >> 1) + 1] = 1;
    else ans[n >> 1] = ans[(n >> 1) + 1] = 1;
    for (int i = 1; i <= n; i++) cout << (ans[i] ? '=' : '-');

    return 0;
}