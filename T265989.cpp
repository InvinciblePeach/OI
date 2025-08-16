#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, m, nums[1000005], ans = INT_MIN;
int max_ = INT_MIN, min_ = INT_MAX;

void dfs(int i, int j) {
    if (i + j == m) { ans = max(ans, max_ - min_); return; }

    int now_max = max_, now_min = min_;

    if (max_ >= 3) { max_ *= 2; dfs(i + 1, j); }
    else if (max_ <= 2 && max_ >= -2) { max_ += 2; dfs(i + 1, j); }
    else if (max_ <= -3) { max_ /= 2; dfs(i + 1, j); }
    max_ = now_max;


    if (min_ >= 3) { min_ /= 2; dfs(i, j + 1); }
    else if (min_ <= 2 && min_ >= -2) { min_ -= 2; dfs(i, j + 1); }
    else if (min_ <= -3) { min_ *= 2; dfs(i, j + 1); }
    min_ = now_min;
}

//void dfs(int now_m) {
//    if (now_m >= m) {
//        int max_ = INT_MIN, min_ = INT_MAX;
//        for (int i = 1; i <= n; i ++) {
//            max_ = max(max_, nums[i]);
//            min_ = min(min_, nums[i]);
//        }
//        ans = max(ans, max_ - min_);
//        return;
//    }
//
//    for (int i = 1; i <= n; i ++) {
//        int tmp = nums[i];
//
//        nums[i] += 2;
//        dfs(now_m + 1);
//        nums[i] = tmp;
//
//        nums[i] -= 2;
//        dfs(now_m + 1);
//        nums[i] = tmp;
//
//        nums[i] *= 2;
//        dfs(now_m + 1);
//        nums[i] = tmp;
//
//        nums[i] /= 2;
//        dfs(now_m + 1);
//        nums[i] = tmp;
//    }
//}

signed main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        cin >> nums[i];
        max_ = max(max_, nums[i]);
        min_ = min(min_, nums[i]);
    }

    dfs(0, 0);

    cout << ans << endl;

    return 0;
}