#include<bits/stdc++.h>

using namespace std;

int N, W;
int v[100005], w[100005], m[100005];
int dp[100005];

int main() {
    cin >> N >> W;
    for (int i = 1; i <= N; i ++) {
        cin >> v[i] >> w[i] >> m[i];
        m[i] --;
    }

    int n = N;
    for (int i = 1; i <= n; i ++) {
        int k = 2;
        for (; k <= m[i]; k *= 2) {
            w[++ N] = w[i] * k;
            v[N] = v[i] * k;
            m[i] -= k;
        }
        if (m[i] > 0) {
            w[++ N] = w[i] * m[i];
            v[N] = v[i] * m[i];
        }
    }

    for (int i = 1; i <= N; i ++) {
        for (int j = W; j >= w[i]; j --) { dp[j] = max(dp[j], dp[j - w[i]] + v[i]); }
    }
    cout << dp[W];
    return 0;
}
