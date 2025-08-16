#include <bits/stdc++.h>

using namespace std;

int n, cnt;
int a[500005], index[500005];
vector<int> nums;

int main() {
    nums.emplace_back(0);
    cin >> n;
    for (int i = 1; i <= n; i ++) { nums.emplace_back(0); }
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        nums[a[i]] = i;
        index[nums[i]] = i;
    }


    while (true) {
        if (nums[1] == 1 && index[nums[1] + 1] - 1 == index[nums[1]]) { break; }
        if (nums[n] == n && index[nums[1] - 1] + 1 == index[nums[n]]) { break; }

        if (index[nums[1] + 1] - 1 != index[nums[1]]) {
            cnt ++;
        } else if (nums[1] != 1 && index[nums[1] - 1] + 1 != index[nums[1]]) {
            cnt ++;
        }

        if (nums[n] != n && index[nums[n] + 1] - 1 != index[nums[n]]) {
            cnt ++;
            int tmp = nums[n];
            nums.insert(nums.begin() + index[tmp], tmp);
            nums.pop_back();
            for (int j = 1; j <= tmp[i])
        } else if (index[nums[n] - 1] + 1 != index[nums[n]]) {
            cnt ++;
        }
    }
    cout << n - cnt << endl;
    return 0;
}