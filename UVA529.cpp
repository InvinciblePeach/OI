#include <bits/stdc++.h>
#define int unsigned

using namespace std;

int n, path[10005] = {0, 1};

bool dfs(int depth, int max_depth) {
    if (depth > max_depth) {
        return path[max_depth] == n;
    }
    if (path[depth - 1] == n) {
        return true;
    }
    if (path[depth - 1] * (long long)(1u << (unsigned long long)(max_depth - depth + 1)) < n) {
        return false;
    }

    bool used[10005] = {false};

    for (int i = depth - 1; i >= 1; i --) {
        int sum_ = path[i] + path[depth - 1];
        if (sum_ > n || sum_ < path[depth - 1] || used[sum_]) {
            continue;
        }
        if (sum_ * ((1u << max_depth) - depth) < n) {
            return false;
        }
        path[depth] = sum_;
        used[signed(sum_)] = true;                  // NOLINT
        if (dfs(depth + 1, max_depth)) {
            return true;
        }
    }

    return false;
}

signed main() {
    while (true) {
        cin >> n;

        if (n == 0) {
            break;
        }

        int max_depth = 1;

        while (!dfs(2, max_depth ++));

        for (int i = 1; i < max_depth - 2; i++) {
            cout << path[i] << ' ';
        }
        cout << path[max_depth - 2] << endl;
    }

    return 0;
}