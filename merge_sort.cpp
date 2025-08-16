#include <bits/stdc++.h>

using namespace std;

int n, nums[100005], tmp[100005];

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
    for (int i = 1; i <= n; i++){
        cout << nums[i] << ' ';
    }
    return 0;
}