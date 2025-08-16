#include <bits/stdc++.h>

using namespace std;

int T, a, b, c, x, y, z;

signed main() {
    freopen("osiris.in", "r", stdin);
    freopen("osiris.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while (T-- > 0) {
        cin >> x >> y >> z >> a >> b >> c;
        if (x < a) {
            if (y > b) {
                if (a - x <= (y - b) / 2) {
                    y -= (a - x) * 2, x = a;
                } else {
                    x += (y - b) / 2;
                    y -= (((y - b) / 2) * 2);
                }
            }

            if (z > c) {
                if (a - x <= (z - c) / 2) {
                    z -= (a - x) * 2, x = a;
                } else {
                    x += (z - c) / 2;
                    z -= (((z - c) / 2) * 2);
                }
            }
        }

        if (y < b) {
            if (x > a) {
                if (b - y <= (x - a) / 2) {
                    x -= (b - y) * 2, y = b;
                } else {
                    y += (x - a) / 2;
                    x -= (((x - a) / 2) * 2);
                }
            }

            if (z > c) {
                if (b - y <= (z - c) / 2) {
                    z -= (a - x) * 2, y = b;
                } else {
                    y += (z - c) / 2;
                    z -= (((z - c) / 2) * 2);
                }
            }
        }

        if (z < c) {
            if (x > a) {
                if (c - z <= (x - a) / 2) {
                    x -= (c - z) * 2, z = c;
                } else {
                    z += (x - a) / 2;
                    x -= (((x - a) / 2) * 2);
                }
            }

            if (y > b) {
                if (c - z <= (y - b) / 2) {
                    y -= (c - z) * 2, z = c;
                } else {
                    z += (y - b) / 2;
                    y -= (((y - b) / 2) * 2);
                }
            }
        }

        cout << (x >= a && y >= b && z >= c ? "YES\n" : "NO\n");
    }
    return 0;
}