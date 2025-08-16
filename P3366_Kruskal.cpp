#include <bits/stdc++.h>

using namespace std;

struct edge {
    int u, v, w;

    inline edge(int u_, int v_, int w_) {
        this->u = u_;
        this->v = v_;
        this->w = w_;
    }

    bool operator< (edge other) const { return this->w < other.w; }
};

int n, m, ans, cnt;
int connect[5005];
vector<edge> edges;

bool kruskal() {
    for (int i = 1; i <= n; i ++) { connect[i] = i; }
    sort(edges.begin(), edges.end());

    for (auto & e : edges) {
        if (connect[e.u] != connect[e.v]) {
            cnt++;
            ans += e.w;
            auto tmp = connect[e.v];
            for (int j = 1; j <= n; j++) {
                if (connect[j] == tmp) { connect[j] = connect[e.u]; }
            }
            if (cnt == n - 1) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    if (kruskal()) { cout << ans << endl; }
    else { cout << "orz" << endl; }
    return 0;
}