#include <bits/stdc++.h>

using namespace std;

bool used[20] = {false};
int n, sum = 0;
int nums[20] = {0}, a[5][5] = {0};

bool dfs(int i, int j) {
    if (i > n) {
        return true;
    }
    for (int x = 1; i <= n * n; i ++) {
        if (used[x]) {
            continue;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n * n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }

    if (n == 1) {
        cout << nums[1] << endl << nums[1];
    }

    sum /= n;
    sort(nums + 1, nums + n * n + 1);

    return 0;
}