#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int a, b, c, d;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> a >> b >> c >> d;
    if (c < a) {
        cout << "Yes\n";
    } else if (c == a && d < b) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}