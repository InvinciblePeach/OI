#include <bits/stdc++.h>

using namespace std;

int n, m, sums[500010] = {0}, nums[500010], ans = INT_MIN;
deque<int> dq;

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
        sums[i] = sums[i - 1] + nums[i];
    }
    dq.push_back(0);
    for (int i = 1; i <= n; i++){
        if (dq.front() < i - m){
            dq.pop_front();
        }
        ans = max(ans, sums[i] - sums[dq.front()]);
        while (!dq.empty() && sums[dq.back()] >= sums[i]){
            dq.pop_back();
        }
        dq.push_back(i);
    }
    cout << ans;
    return 0;
}