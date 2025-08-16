#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int t;
int a, b, c;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        cin >> a >> b >> c;
        if ((a + b + c) % 3) {
            cout << "NO\n";
        } else {
            if (a <= (a + b + c) / 3 && b <= (a + b + c) / 3)
            cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}