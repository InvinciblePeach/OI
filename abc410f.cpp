#include <bits/stdc++.h>
#define int long long

using namespace std;

int T, H, W, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {

        cin >> H >> W;
        vector<string> grid(H);
        for (int i = 0; i < H; i++) cin >> grid[i];

        vector<vector<int>> A(H, vector<int>(W));
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                A[i][j] = (grid[i][j] == '#' ? 1 : -1);

        ans = 0;
        vector<int> sum(W);

        for (int u = 0; u < H; u++) {
            fill(sum.begin(), sum.end(), 0);
            for (int d = u; d < H; d++) {
                for (int j = 0; j < W; j++) sum[j] += A[d][j];

                unordered_map<int, int> cnt;
                cnt[0] = 1;
                for (int j = 0, tmp = 0; j < W; j++) ans += cnt[tmp += sum[j]]++;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}