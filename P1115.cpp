#include<bits/stdc++.h>
// AC

using namespace std;

int n;
vector<int> a;

int mq(){
    int sum = 0;
    int ans = -INT_MAX;
    for (int i: a){
        sum = max(sum + i, i);
        ans = max(sum, ans);
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        a.push_back(x);
    }
    cout << mq();
    return 0;
}
