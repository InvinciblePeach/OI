#include <bits/stdc++.h>

using namespace std;

long long N, C, cnt = 0;
int nums[200005];
unordered_map<int, vector<int>> Hash;

int main(){
    cin >> N >> C;
    for (int i = 1; i <= N; i++){
        cin >> nums[i];
        Hash[nums[i] - C].push_back(nums[i]);
    }

    for (int i = 1; i <= N; i++){
        cnt += Hash[nums[i]].size();
    }

    cout << cnt << endl;
    return 0;
}