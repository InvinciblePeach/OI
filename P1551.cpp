#include <bits/stdc++.h>

using namespace std;

int n, m, p, nums[10005];

int main() {
    cin >> n >> m >> P;

    for (int i = 1; i <= n; i ++) {
        nums[i] = i;
    }

    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        int tmp = nums[y];
        for (int j = 1; j <= n; j ++)
            if (nums[j] == tmp) { nums[j] = nums[x]; }
    }

    for (int i = 1; i <= P; i ++) {
        int x, y;
        cin >> x >> y;
        if (nums[x] == nums[y]) { cout << "Yes" << endl; }
        else { cout << "No" << endl; }
    }

    return 0;
}