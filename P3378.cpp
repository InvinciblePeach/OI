#include <bits/stdc++.h>

using namespace std;

priority_queue<int, vector<int>, greater<>> pq; // NOLINT

int n;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            pq.emplace(x);
        } else if (op == 2) {
            cout << pq.top() << endl;
        } else if (op == 3) {
            pq.pop();
        }
    }
    return 0;
}