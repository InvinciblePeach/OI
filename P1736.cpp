#include <bits/stdc++.h>

using namespace std;

bool a[2505][2505];
int n, m, max_ = 0;
int dp[2505][2505] = {0}/*主对角线最长吃到鱼的数量*/, g[2505][2505] = {0}/*副对角线最长吃到鱼的数量*/;

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (a[i][j]){
                dp[i][j] = 1, g[i][j] = 1;
                if (a[i - 1][j - 1]){
                    bool flag = true;
                    for (int k = 1; k <= dp[i - 1][j - 1]; k++){
                        if (a[i - k][j] || a[i][j - k]){      // 此矩阵内还有鱼
                            flag = false;
                            dp[i][j] = k;
                            break;
                        }
                    }
                    if (flag){
                        dp[i][j] += dp[i - 1][j - 1];
                    }
                }
                if(a[i - 1][j + 1]){
                    bool flag = true;
                    for (int k = 1; k <= g[i - 1][j + 1]; k++){
                        if (a[i - k][j] || a[i][j + k]){      // 此矩阵内还有鱼
                            flag = false;
                            g[i][j] = k;
                            break;
                        }
                    }
                    if (flag){
                        g[i][j] += g[i - 1][j + 1];
                    }
                }
                max_ = max({max_, dp[i][j], g[i][j]});
            }
        }
    }

    cout << max_ << endl;

    return 0;
}