#include<bits/stdc++.h>
// 3, 5, 9 WA

using namespace std;

int n, m;
int a[500005] = {0};

int ans(){
    int sum = a[0];
    int ans = sum;
    int index = 0;
    for (int i = 1; i < n; i++){
        while (i - index >= m - 1){
            sum -= a[index];
            index++;
        }
        if (sum > 0){
            sum += a[i];
        }
        else{
            sum = a[i];
            index = i;
        }
        ans = max(sum, ans);
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    cout << ans();
    return 0;
}
