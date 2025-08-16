#include <bits/stdc++.h>

using namespace std;

int n, m;
int a[45], b[45];
int dp[45][45];

int main() {
    cin >> n >> m;
    if (n == m) {
        int sum = 0;
        int a_, b_;
        for (int i = 1; i <= n; i ++) {
            cin >> a_ >> b_;
            sum += b_;
        }
        cout << sum << endl;
    }
    return 0;
}