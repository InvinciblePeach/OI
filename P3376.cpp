#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) {
        this->v = v_;
        this->w = w_;
    }
};

int n, m, s, t;
vector<edge> graph[505];

void bfs() {
    queue<int, >
}

void dinic() {
    ;
}

int main() {
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    ;

    return 0;
}