#include <bits/stdc++.h>

using namespace std;

int N, ans = 0, A[100005], B[100005], dp[100005];

int main() {
    memset(dp, 0x80, sizeof(dp));
    cin >> N;
    for (int i = 1; i <= N; i ++) {
        int n;
        cin >> n;
        A[n] = i;
    }
    for (int i = 1; i <= N; i ++) {
        int n;
        cin >> n;
        B[i] = A[n];
    }

    memset(dp, 0x3f, sizeof(dp));

    for (int i = 1; i <= N; i ++) {

        int l = 0, r = i - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (dp[mid] < B[i]) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }

        dp[r + 1] = B[i];
        ans = max(ans, r + 1);
    }

    cout << ans << endl;

    return 0;
}