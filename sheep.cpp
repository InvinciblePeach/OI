#include <bits/stdc++.h>

using namespace std;

int T, n, x[200005], y[200005], u[200005], v[200005];

int main() {
    cin >> T;
    while (T --> 0) {
        cin >> n;
        for (int i = 1; i <= n; i ++) {
            cin >> x[i] >> y[i] >> u[i] >> v[i];
        }
    }
    return 0;
}