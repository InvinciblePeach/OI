#include <bits/stdc++.h>

using namespace std;

int n, dp[105][105], v[105], w[105], V;
vector<int> graph[105];

void DP(int i){
    dp[i][0] = 0;
    for (int j = v[i]; j <= V; j++){
        dp[i][j] = w[i];
    }
    for (auto y_i: graph[i]){
        DP(y_i);
        for (int j = V; j >= v[i]; j--){
            for (int k = 0; k <= j - v[i]; k++){
                dp[i][j] = max(dp[i][j], dp[i][j - k] + dp[y_i][k]);
            }
        }
    }
}

int main(){
    cin >> n >> V;
    int root;
    for (int i = 1; i <= n; i++){
        int p;
        cin >> v[i] >> w[i] >> p;
        if (p == -1){
            root = i;
        }
        else {
            graph[p].push_back(i);
        }
    }
    DP(root);
    cout << dp[root][V] << endl;
    return 0;
}