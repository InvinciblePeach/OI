#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;

int n, ans, nums[100005], tmp[100005];
unordered_map<string, int> map_;

void merge_sort(int l, int r) {
    if (r - l <= 1) { return; }
    int mid = l + ((r - l) / 2);
    merge_sort(l, mid);
    merge_sort(mid, r);
    int i = l, j = l;
    int k = mid;
    while (j < r) {
        if (i >= mid || (k < r && nums[i] > nums[k])) {
            tmp[j++] = nums[k ++];
            ans += mid - i;
        } else {
            tmp[j ++] = nums[i ++];
        }
    }
    for (int x = l; x < r; x ++) {
        nums[x] = tmp[x];
    }
}


signed main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        string s;
        cin >> s;
        map_[s] = i;
    }
    for (int i = 1; i <= n; i ++) {
        string s;
        cin >> s;
        nums[i] = map_[s];
    }
    merge_sort(1, n + 1);
    cout << ans << endl;
    return 0;
}