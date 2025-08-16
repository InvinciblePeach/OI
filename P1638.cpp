#include <bits/stdc++.h>

using namespace std;

int n, m, l = 1, r = 1, k = 1, ans_l = 0, ans_r = INT_MAX, painters[2005], pictures[1000005];

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> pictures[i];
    }

    painters[pictures[1]] = 1;

    while (l <= r && r <= n){
        if (k == m){
            if (ans_r - ans_l + 1 > r - l + 1){
                ans_l = l;
                ans_r = r;
            }
            painters[pictures[l]] --;
            if (!painters[pictures[l]]){ k --; }
            l ++;
        }
        else{
            r++;
            painters[pictures[r]] ++;
            if (painters[pictures[r]] == 1){
                k ++;
            }
        }
    }

    cout << ans_l << ' ' << ans_r << endl;

    return 0;
}