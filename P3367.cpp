#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) {
        this->v = v_;
        this->w = w_;
    }
};

int n, m, nums[10005];
vector<edge> graph;

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        nums[i] = i;
    }

    for (int i = 1; i <= m; i ++) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            int tmp = nums[y];
            for (int j = 1; j <= n; j ++)
                if (nums[j] == tmp) { nums[j] = nums[x]; }
        } else {
            if (nums[x] == nums[y]) { cout << 'Y' << endl; }
            else { cout << 'N' << endl; }
        }
    }

    return 0;
}