#include <bits/stdc++.h>

using namespace std;

int N, dp1[605][605], dp2[605][605], nums[605], sums[605];

int main(){
    memset(dp1, 0x3f, sizeof(dp1));
    memset(dp2, 0x80, sizeof(dp2));
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> nums[i];
        nums[i + N] = nums[i];
    }
    for (int i = 1; i <= 2 * N; i++){ sums[i] = sums[i - 1] + nums[i]; }
    for (int i = 1; i <= 2 * N; i++){
        dp1[i][i] = 0;
        dp2[i][i] = 0;
    }
    for (int len = 2; len <= N; len++){
        for(int l = 1; l <= 2 * N - len + 1; l++){
            int r = l + len - 1;
            for (int k = l; k < r; k++){
                dp1[l][r] = min(dp1[l][r], dp1[l][k] + dp1[k + 1][r] + sums[r] - sums[l - 1]);
                dp2[l][r] = max(dp2[l][r], dp2[l][k] + dp2[k + 1][r] + sums[r] - sums[l - 1]);
            }
        }
    }
    int _min = INT_MAX, _max = INT_MIN;
    for (int i = 1; i <= N; i++){
        _min = min(_min, dp1[i][i + N - 1]);
        _max = max(_max, dp2[i][i + N - 1]);
    }
    cout << _min << endl;
    cout << _max << endl;
    return 0;
}
