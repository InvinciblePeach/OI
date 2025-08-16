#include <bits/stdc++.h>

using namespace std;

int n, m, a[105];

bool check(const vector<int> & nums) {
    for (int i = 1; i <= n; i ++) {
        if (a[i] != nums[i]) { return false; }
    }
    return true;
}

void bfs() {
    queue<tuple<int, int, vector<int>, vector<int>>> q;
    q.emplace(1, 0, vector<int>(), vector<int>(105, -1));
    while (!q.empty()) {
        int u = get<0>(q.front()), i = get<1>(q.front());
        vector<int> path = get<2>(q.front()), nums = get<3>(q.front());
        q.pop();

        if (check(nums)) {
            cout << i << endl;
            for (auto x : path) { cout << x << ' '; }
            cout << endl;
            exit(0);
        }

        i ++;
        path.emplace_back(u);
        if (u > 1) { q.emplace(u - 1, i, path, nums); }
        if (u < n) { q.emplace(u + 1, i, path, nums); }
        nums[u] = i % m;
        q.emplace(u, i, path, nums);
    }
    cout << "NO" << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    bfs();
    return 0;
}