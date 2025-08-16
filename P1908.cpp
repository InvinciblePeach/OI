#include <bits/stdc++.h>

using namespace std;

long long n, nums[500015], tmp[500015], ans;

void merge_sort(long long l, long long r){
    if (r - l <= 1){ return; }
    long long mid = l + ((r - l) / 2);
    merge_sort(l, mid);
    merge_sort(mid, r);
    long long i = l, j = l;
    long long k = mid;
    while(j < r){
        if (i >= mid || (k < r && nums[i] > nums[k])) {
            tmp[j++] = nums[k++];
            ans += mid - i;
        }
        else{
            tmp[j++] = nums[i++];
        }
    }
    for (int _ = l; _ < r; _++){
        nums[_] = tmp[_];
    }
}


int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }
    merge_sort(1, n + 1);
    cout << ans;
    return 0;
}