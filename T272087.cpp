#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;
int n, cnt;
int nums[5005];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    sort(nums + 1, nums + n + 1, greater<>());

    int l = 1, r = 1, sum = 0;

    while (l <= n && r <= n) {
        if (nums[l] < sum) {
            sum = 0;
            end_ += n - r + 1;
            l++;
            while (r <= l) {
                r++;
            }
            continue;
        }

        int tmp = r;
        for (; tmp <= n; tmp++) {
            if (nums[tmp] >= nums[l]) {
                break;
            }
        }
        if (tmp != n + 1) {
            sum = 0;
            end_ += n - tmp + 1;
            l++;
            while (r <= l) {
                r++;
            }
            continue;
        }

        if (r < n) {
            r++;
            sum += nums[r];
        } else {
            l++;
        }
    }

    cout << cnt << endl;

    return 0;
}