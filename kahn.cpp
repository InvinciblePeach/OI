#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> ans;
vector<int> graph[10005];
int in_degree[100005];
bool visited[100005];

void kahn() {
    while (true) {
        bool flag = false;
        for (int i = 1; i <= n; i ++) {
            if (!in_degree[i] && !visited[i]) {
                ans.emplace_back(i);
                visited[i] = true;
                for (auto e : graph[i]) {
                    in_degree[e]--;
                }
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        in_degree[v] ++;
    }

    kahn();

    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}