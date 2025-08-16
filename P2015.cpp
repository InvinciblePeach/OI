#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    inline edge(const int &v_, const int &w_) {
        this->v = v_;
        this->w = w_;
    }
};

int N, Q;
int dp[105][105];
vector<edge> edges[105];

void DP(int u, int father) {
    fill(dp[u], dp[u] + Q, INT_MIN);
    dp[u][0] = 0;
    for (auto e : edges[u]) {
        if (e.v != father) {
            DP(e.v, u);
            for (int k = Q; k >= 1; k --) {
                for (int j = 0; j < k; j ++) {
                    dp[u][k] = max(dp[u][k], dp[u][j] + dp[e.v][k - j - 1] + e.w);
                }
            }
        }
    }
}

int main() {
    cin >> N >> Q;

    for (int i = 1; i < N; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }

    DP(1, 0);

    cout << dp[1][Q] << endl;

    return 0;
}