#include <bits/stdc++.h>

using namespace std;

int n, nums[10005], ans = 0;

int main(){
    memset(nums, 0x3f, sizeof(nums));
    nums[0] = 0;
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }

    sort(nums, nums + n);

    for (int i = 1; i <= n; i++){
        ans += abs(nums[(n + 1) / 2] - nums[i]);
    }

    cout << ans << endl;
    return 0;
}
