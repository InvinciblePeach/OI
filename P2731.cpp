#include <bits/stdc++.h>

using namespace std;

int m, cnt, degree[505];
int del[505];
stack<int> ans; // NOLINT
int graph[505][505];

void dfs(int u) {
    for (int i = max(1, del[u]); i <= 505; i = del[u]) {
        if (graph[u][i]) {
            graph[u][i] --;
            graph[i][u] --;
            dfs(i);
        } else { del[u] = i + 1; }
    }
    ans.emplace(u);
}

void print() {
    cout << ans.top() << endl;
    ans.pop();
}

int main() {
    cin >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] ++;
        graph[v][u] ++;
        degree[u] ++, degree[v] ++;
    }

    int now = 1;
    for (int i = 1; i <= 505; i ++) {
        if (degree[i] % 2) {
            cnt ++;
            if (cnt == 1) {
                now = i;
                break;
            }
        }
    }

    dfs(now);

    while (!ans.empty()) { print(); }
    return 0;
}