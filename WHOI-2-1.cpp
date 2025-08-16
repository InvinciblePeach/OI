#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

int T;
ull n;
ull nums[1000005];

ull f(ull x){
    ull ans = 0;
    while(x){
        ans = ans * 10 + x % 10;
        x = x / 10;
    }
    return ans;
}

int main(){
    nums[0] = 0;
    for (int i = 1; i <= 1000001; i++){
        nums[i] = nums[i - 1];
        for (int j = 1; f(nums[i - 1] + j) <= i; j++) {
            ull tmp = f(nums[i - 1] + j);
            if (tmp <= i) {
                nums[i] = nums[i - 1] + j;
            }
        }
    }
    cin >> T;
    for (int i = 1; i <= T; i++){
        cin >> n;
        cout << nums[n] << endl;
    }
    return 0;
}