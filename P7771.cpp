#include <bits/stdc++.h>

using namespace std;

int n, m, cnt, degree[100005][2];
int del[100005];
stack<int> ans; // NOLINT
vector<int> graph[100005];

void dfs(int u) {
    for (int i = del[u]; i < graph[u].size(); i = del[u]) {
        if (graph[u][i]) {
            del[u] = i + 1;
            dfs(graph[u][i]);
        }
    }
    ans.emplace(u);
}

void print() {
    cout << ans.top() << ' ';
    ans.pop();
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        degree[u][1] ++, degree[v][0] ++;
    }

    for (int i = 1; i <= n; i ++) { sort(graph[i].begin(), graph[i].end()); }

    int now = INT_MAX;
    for (int i = 1; i <= n; i ++) {
        if (cnt > 2) {
            cout << "No" << endl;
            return 0;
        }

        if (degree[i][1] != degree[i][0]) {
            cnt ++;
            if (cnt == 1) {
                now = i;
            }
        }
        else if (!cnt) { now = min(now, i); }
    }

    dfs(now);

    while (!ans.empty()) { print(); }
    cout << endl;
    return 0;
}