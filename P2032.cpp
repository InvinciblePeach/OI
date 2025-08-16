#include <bits/stdc++.h>

using namespace std;

int n, k, nums[2000005];
deque<int> dq; //NOLINT

int main(){
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }
    for (int i = 1; i <= n; i++){
        while (!dq.empty() && dq.front() < i - k + 1){
            dq.pop_front();
        }
        while (!dq.empty() && nums[dq.back()] < nums[i]){
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k){
            cout << nums[dq.front()] << endl;
        }
    }
    return 0;
}