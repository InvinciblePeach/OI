#include<bits/stdc++.h>

using namespace std;

int n, ans = INT_MIN, num[1000005], dp[100000005];

int main(){
    memset(dp, 0x8f, sizeof(dp));
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> num[i];
    }
    for (int i = 1; i <= n; i++){
        int l = 0, r = i - 1;
        while (l < r){
            int mid = (l + r + 1) / 2;
            if (dp[mid] >= num[i]){
                l = mid;
            }
            else{
                r = mid - 1;
            }
        }

        dp[r + 1] = num[i];
        ans = max(ans, r + 1);
    }
    cout << ans << endl;
    return 0;
}
