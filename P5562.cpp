#include<bits/stdc++.h>

using namespace std;

int T, N, M, v[105][105], f[10005];

int main(){
    cin >> T >> N >> M;
    for (int i = 1; i <= T; i++){
        for (int j = 1; j <= N; j++){
            cin >> v[i][j];
        }
    }
    for (int _ = 1; _ < T; _++){
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= N; i++){
            for (int j = v[_][i]; j <= M; j++){
                f[j] = max(f[j], f[j - v[_][i]] - v[_][i] + v[_ + 1][i]);
            }
        }
        M += f[M];
    }
    cout << M;
    return 0;
}
