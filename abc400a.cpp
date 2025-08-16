#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    cout << (400 % n ? -1 : 400 / n) << '\n';

    return 0;
}