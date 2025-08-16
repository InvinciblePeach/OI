#include <bits/stdc++.h>

using namespace std;

long long n, ans = 0;
priority_queue<long long, vector<long long>, greater<>> pq; //NOLINT

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        long long num;
        cin >> num;
        pq.push(num);
    }

    for (int i = 1; i < n; i++){
        long long x = pq.top();
        pq.pop();
        long long y = pq.top();
        pq.pop();
        ans += x + y;
        pq.push(x + y);
    }

    cout << ans << endl;

    return 0;
}