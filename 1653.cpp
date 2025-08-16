#include <bits/stdc++.h>

using namespace std;

int n = 1, nums[100005], tmp[100005], ans;

void merge_sort(int l, int r){
    if (r - l <= 1){ return; }
    int mid = l + ((r - l) / 2);
    merge_sort(l, mid);
    merge_sort(mid, r);
    int i = l, j = l;
    int k = mid;
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
    while (cin >> nums[n]){
        n++;
    }
    merge_sort(1, n);
    cout << ans;
    return 0;
}