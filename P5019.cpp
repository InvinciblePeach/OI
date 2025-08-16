#include <bits/stdc++.h>

using namespace std;

int n, nums[100005];
unsigned long long ans;

int main(){
    cin >> n;

    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }

    ans = nums[1];

    for (int i = 2; i <= n; i++){
        if (nums[i] > nums[i - 1]){
            ans += nums[i] - nums[i - 1];
        }
    }

    cout << ans << endl;

    return 0;
}