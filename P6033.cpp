#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, ans = 0;
priority_queue<int, vector<int>, greater<>> pq; //NOLINT

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        int num;
        cin >> num;
        pq.emplace(num);
    }

    for (int i = 1; i < n; i++){
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        ans += x + y;
        pq.emplace(x + y);
    }

    cout << ans << endl;

    return 0;
}