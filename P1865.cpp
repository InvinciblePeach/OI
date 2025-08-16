#include <bits/stdc++.h>

using namespace std;

int n, m, l, r;
int f[1000006];
bool p[1000006];

int main() {
    cin >> n >> m;

    for (int i = 2; i <= m; i ++) { P[i] = true; }

    for (int i = 2; i <= m; i ++) {
        if (P[i]) {
            for (int j = i * 2; j <= m; j += i) { P[j] = false; }
            f[i] = f[i - 1] + 1;
        } else { f[i] = f[i - 1]; }
    }

    while (n --> 0) {
        cin >> l >> r;
        if (l < 1 || r > m) { cout << "Crossing the line" << endl; }
        else { cout << f[r] - f[l - 1] << endl; }
    }
    return 0;
}