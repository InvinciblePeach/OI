#include <bits/stdc++.h>

using namespace std;

int ans = 0, n, nums[105], f[105], g[105];

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
        f[i] = g[i] = 1;
    }
    for (int i = n - 1; i >= 1; i--){
        for (int j = i + 1; j <= n; j++){
            if (nums[i] > nums[j]){
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }
    for (int i = 2; i <= n; i++){
        for (int j = 1; j < i; j++){
            if (nums[i] > nums[j]){
                g[i] = max(g[i], g[j] + 1);
            }
        }
    }
    for (int i = 1; i <= n; i++){
        int a = f[i] + g[i] - 1;
        ans = max(ans, a);
    }
    cout << n - ans << endl;
    return 0;
}