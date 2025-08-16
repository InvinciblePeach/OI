#include <bits/stdc++.h>

using namespace std;

int n, nums[100005], C[100005], A[100005];

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }
    memcpy(C, nums, sizeof(nums));
    sort(C, C + n);
    int l = unique(C, C + n) - C;
    for (int i = 1; i <= l; i++){
        A[i] = lower_bound(C, C + l, nums[i]) - C;
        cout << A[i] << ' ';
    }
    return 0;
}