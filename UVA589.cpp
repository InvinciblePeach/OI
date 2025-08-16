#include <bits/stdc++.h>

using namespace std;

int n, m;
int graph[25][25];

void bfs(int x, int y) {
    ;
}

int main() {
    while (true) {
        cin >> n >> m;

        if (n + m == 0) { break; }

        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= m; j ++) {
                cin >> graph[i][j];
            }
        }
    }
    return 0;
}