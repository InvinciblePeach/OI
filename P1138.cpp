#include <bits/stdc++.h>

using namespace std;

int n, k, nums[10005];

int main(){
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }

    sort(nums + 1, nums + n + 1);

    long long len = unique(nums + 1, nums + n + 1) - nums;

    if (k >= len){
        cout << "NO RESULT" << endl;
    }
    else {
        cout << nums[k] << endl;
    }

    return 0;
}