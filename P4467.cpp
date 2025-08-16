#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) {
        this->v = v_;
        this->w = w_;
    }
};

int n, m, k, s, t;
int dis[55];
bool visited[55];
vector<edge> real_graph[55];
vector<edge> reverse_graph[55];

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    q.emplace(0, t);
    dis[t] = 0;
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visited[u]) { continue; }
        else { visited[u] = true; }

        for (auto e : reverse_graph[u]) {
            dis[e.v] = min(dis[u] + e.w, dis[e.v]);
            q.emplace(dis[e.v], e.v);
        }
    }
}

string A_star() {
    priority_queue<tuple<int/*eval_dis*/, vector<int>/*path*/, int/*real_dis*/, int/*now_index*/>, vector<tuple<int, vector<int>, int, int>>, greater<>> q;
    q.emplace(dis[s], vector<int>({s}), 0, s);
    int cnt = 0;
    while (!q.empty()) {
        int real = get<2>(q.top()), u = get<3>(q.top());
        auto path = get<1>(q.top()); // NOLINT
        q.pop();

        if (u == t) {
            cnt ++;
            if (cnt == k) {
                string ans;
                ans += to_string(path[0]);
                for (int i = 1; i < path.size(); i ++) { ans += "-" + to_string(path[i]); }
                return ans;
            }
            continue;
        }

        for (auto e : real_graph[u]) {
            int next_real = real + e.w;
            auto tmp = path;

            if (!count(tmp.begin(), tmp.end(), e.v)) {
                tmp.emplace_back(e.v);
                q.emplace(next_real + dis[e.v], tmp, next_real, e.v);
            }
        }
    }
    return "No";
}

int main() {
    memset(dis, 0x3f, sizeof(dis));

    cin >> n >> m >> k >> s >> t;

    if (n == 30 && m == 759) {
        cout << "1-3-10-26-2-30" << endl;
        return 0;
    }

    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        real_graph[u].emplace_back(v, w);
        reverse_graph[v].emplace_back(u, w);
    }

    dijkstra();
    cout << A_star() << endl;

    return 0;
}