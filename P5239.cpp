#include <bits/stdc++.h>

using namespace std;

int q;
int sum[1005][1005];

int main() {
    for (int i = 1; i <= 1001; i ++) {
        for (int j = 1; j <= 1001; j ++) { sum[i][j] = (sum[i - 1][j - 1] + sum[i - 1][j] + i) % 19260817; }
    }
    cin >> q;
    for (int i = 1; i <= q; i ++) {
        int n, m;
        cin >> n >> m;
        cout << sum[m][n] << endl;
    }
    return 0;
}