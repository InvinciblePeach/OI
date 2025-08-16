#include <bits/stdc++.h>

using namespace std;

int T;
unsigned long long a[1005][1005];

int main() {
    for (int i = 1; i <= 1001; i ++) {
        for (int j = 1; j <= 1001; j ++) {
            if (i == 1) { a[i][j] = 1; continue; }
            if (j == 1) { a[i][j] = i; continue; }
            a[i][j] = a[i][j - 1] ^ a[i - 1][j];
        }
    }
    cin >> T;
    while (T --> 0) {
        unsigned long long ans = 0;
        int l_1, l_2, r_1, r_2;
        cin >> l_1 >> l_2 >> r_1 >> r_2;
        for (int i = l_1; i <= l_2; i ++) {
            for (int j = r_1; j <= r_2; j ++) {
                ans ^= a[i][j];
            }
        }
        cout << ans << endl;
    }
    return 0;
}