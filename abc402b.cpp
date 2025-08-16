#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int t;
queue<int> q;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        int a, x;
        cin >> a;
        if (a == 1) {
            cin >> x;
            q.emplace(x);
        } else {
            if (q.size()) {
                cout << q.front() << '\n';
                q.pop();
            }
        }
    }

    return 0;
}