#include<bits/stdc++.h>

using namespace std;

int ans = INT_MIN, missile[1000005], dp[10000005];

int main(){
    memset(dp, 0x80, sizeof(dp));
    int n = 1;

    while(cin >> missile[n])
        n++;
    n--;

    for (int i = 1; i <= n; i++){

        int l = 0, r = i - 1;
        while (l < r){
            int mid = (l + r + 1) / 2;
            if (dp[mid] >= missile[i]){
                l = mid;
            }
            else{
                r = mid - 1;
            }
        }

        dp[r + 1] = missile[i];
        ans = max(ans, r + 1);
    }

    cout << ans << endl;

    ans = 0;
    memset(dp, 0x3f, sizeof(dp));

    for (int i = 1; i <= n; i++){

        int l = 0, r = i - 1;
        while (l < r){
            int mid = (l + r + 1) / 2;
            if (dp[mid] < missile[i]){
                l = mid;
            }
            else{
                r = mid - 1;
            }
        }

        dp[r + 1] = missile[i];
        ans = max(ans, r + 1);
    }

    cout << ans << endl;

    return 0;
}
