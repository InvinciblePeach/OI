#include<bits/stdc++.h>

using namespace std;

int n;
int h[6005];
int p[6005][6005] = {0};

int dfs(int i = 5, bool flag = 1){
    int ans = INT_MIN;
    bool f = 0;
    for (int j = 1; j <= n; j++){
        if (p[i][j] == 1){
            if (flag) {
                ans = max({dfs(j, 0) + h[i], dfs(j), ans});
            }
            else {
                ans = max({dfs(j), ans});
            }
            f = 1;
        }
    }
    if (!f){
        ans = f * h[i];
    }
    cout << i << ' ' << ans << endl;
    return ans;
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> h[i];
    }
    for (int i = 1; i < n; i++){
        int K, L;
        cin >> L >> K;
        p[K][L] = 1;
    }
//    for (int i = 1; i <= n; i++){
//        for (int j = 1; j <= n; j++){
//            cout << p[i][j] << ' ';
//        }
//        cout << endl;
//    }
    cout << dfs();
    return 0;
}
