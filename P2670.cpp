#include <bits/stdc++.h>

using namespace std;

int n, m;
int dx[] = {-1,1, 0, 0, -1,-1, 1, 1};
int dy[] = {0, 0, -1,1, 1, -1, -1,1};
char graph[105][105];

int main(){
    cin >> n >> m;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> graph[i][j];
            if (graph[i][j] == '?'){
                graph[i][j] = '0';
            }
        }
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (graph[i][j] == '*'){
                continue;
            }
            for (int k = 0; k < 8; k++){
                if (graph[i + dx[k]][j + dy[k]] == '*'){
                    graph[i][j] ++;
                }
            }
        }
    }


    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cout << graph[i][j];
        }
        cout << endl;
    }

    return 0;
}