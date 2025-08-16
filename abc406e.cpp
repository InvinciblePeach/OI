#include <bits/stdc++.h>
#define int long long

using namespace std;
const int mod = 998244353;
const int MAXM = 70;

int N, T, K;
int cnt[MAXM][MAXM], sum[MAXM][MAXM], pw2[MAXM];
vector<int> bits;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pw2[0] = 1;
    for (int i = 1; i < MAXM; i++)
        pw2[i] = (pw2[i - 1] << 1) % mod;
    for (int j = 0; j < MAXM; j++) {
        cnt[j][0] = 1;
        sum[j][0] = 0;
        for (int k = 1; k <= j; k++) {
            cnt[j][k] = (cnt[j - 1][k] + cnt[j - 1][k - 1]) % mod;
            sum[j][k] = (sum[j - 1][k] + sum[j - 1][k - 1] + cnt[j - 1][k - 1] * pw2[j - 1] % mod) % mod;
        }
    }

    cin >> T;
    while (T --> 0) {
        cin >> N >> K;
        bits.clear();
        while (N) {
            bits.emplace_back(N & 1);
            N >>= 1;
        }
        int len = bits.size();
        int ans = 0;
        int res = 0;
        int m = K;
        for (int i = len - 1; i >= 0; --i) {
            if (bits[i] == 1) {
                if (m <= i) {
                    int a = cnt[i][m], b = sum[i][m];
                    (ans += res * a + b) %= mod;
                }
                (res += pw2[i]) %= mod;
                m--;
                if (m < 0) break;
            }
        }
        if (m == 0) (ans += res) %= mod;
        cout << ans << '\n';
    }
    return 0;
}