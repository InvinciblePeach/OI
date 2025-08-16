#include <bits/stdc++.h>

using namespace std;

int n, cnt;
char now = CHAR_MAX;
int degree[130];
bool visited[130][130];
vector<char> graph[130];
stack<char> ans; // NOLINT

void dfs(char u) {
    for (auto v : graph[u]) {
        if (!visited[u][v]) {
            visited[u][v] = true;
            visited[v][u] = true;
            dfs(v);
        }
    }
    ans.emplace(u);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        char u, v;
        cin >> u >> v;
        degree[u] ++, degree[v] ++;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    for (int i = 1; i <= 130; i ++) {
        sort(graph[i].begin(), graph[i].end());
    }
    for (int i = 1; i <= 130; i ++) {
        if (cnt > 2) {
            cout << "No Solution" << endl;
            return 0;
        }
        if (degree[i] == 0) { continue; }
        if (degree[i] % 2) {
            cnt ++;
            if (cnt == 1) {
                now = char(i);
            }
        }
        else if (!cnt) { now = min(now, char(i)); }
    }
    if (cnt && cnt != 2) {
        cout << "No Solution" << endl;
        return 0;
    }
    dfs(now);
    if (ans.size() - 1 < n) {
        cout << "No Solution" << endl;
        return 0;
    }
    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
    cout << endl;
    return 0;
}