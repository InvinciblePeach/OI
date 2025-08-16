#include <bits/stdc++.h>

using namespace std;

int n = 1, ans;
pair<int, int> nums[500005]; // NOLINT

int main() {
    for (; cin >> nums[n].first; n ++) {
        nums[n].second = n;
    } n --;

    sort(nums + 1, nums + n + 1);

    for (int i = 1; i <= n; i ++) {
        int max_index = i;
        if (nums[max_index].first == INT_MIN || nums[max_index].second == INT_MIN) { continue; }
        for (int j = i + 1; j <= n; j ++) {
            if (nums[j].second < nums[i].second || nums[j].first < nums[max_index].first) { continue; }
            max_index = j;
        }
        ans += nums[max_index].first - nums[i].first;
        nums[max_index].first = INT_MIN, nums[max_index].second = INT_MIN;
    }
    cout << ans << endl;
    return 0;
}