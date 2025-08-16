#include <bits/stdc++.h>

using namespace std;

bool nums[15][15];
int m, n, sx, sy, ex, ey;

bool flag = false, visited[15][15] = {false};

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

void dfs(int x, int y, const string& path){
    if (x == ex && y == ey){
        cout << path << endl;
        flag = true;
        return;
    }
    for (int i = 0; i < 4; i ++){
        int now_x = x + dx[i];
        int now_y = y + dy[i];

        if (!visited[now_x][now_y] && nums[now_x][now_y] && 1 <= now_x <= m && 1 <= now_y <= n){
            visited[now_x][now_y] = true;
            dfs(now_x, now_y, path + "->" + "(" + to_string(now_x) + "," + to_string(now_y) + ")");
            visited[now_x][now_y] = false;
        }
    }
}

int main(){
    cin >> m >> n;
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            cin >> nums[i][j];
        }
    }

    cin >> sx >> sy >> ex >> ey;

    visited[sx][sy] = true;

    string p = "(" + to_string(sx) + "," + to_string(sy) + ")";

    dfs(sx, sy, p);

    if (!flag){
        cout << -1 << endl;
    }

    return 0;
}