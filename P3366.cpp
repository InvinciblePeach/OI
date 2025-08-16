#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    inline edge(int v_, int w_) {
        this->v = v_;
        this->w = w_;
    }
};

int n, m, ans;
vector<edge> graph[5005];
int dis[5005];
bool in_tree[5005], flag;

void prim() {
    for (int i = 1; i <= n; i ++) {
        dis[i] = INT_MAX;
    }

    int cnt = 0;

    dis[1] = 0;

    while (cnt <= n - 1) {
        int min_ = INT_MAX, min_index = -1;
        for (int i = 1; i <= n; i ++) {
            if (dis[i] < min_ && !in_tree[i]) {
                min_ = dis[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            flag = true;
            cout << "orz" << endl;
            return;
        }

        ans += min_;
        in_tree[min_index] = true;
        cnt ++;

        for (auto & e : graph[min_index]) {
            dis[e.v] = min(dis[e.v], e.w);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v,w);
        graph[v].emplace_back(u,w);
    }

    prim();

    if (!flag) {
        cout << ans << endl;
    }

    return 0;
}