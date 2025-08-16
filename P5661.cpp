#include <bits/stdc++.h>
#define time first
#define price second

using namespace std;

int n, ans;
deque<pair<int, int>> q; // NOLINT

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        int flag, p, t;
        cin >> flag >> p >> t;

        if (flag == 0) {
            q.emplace_back(t, p);
            ans += p;
            continue;
        }

        while (q.front().time < t - 45 && !q.empty()) { q.pop_front(); }

        bool f = true;
        int cnt = 0;
        for (auto j = q.begin(); cnt < q.size(); j ++, cnt ++) { // NOLINT
            if (j->price >= p) {
                j->time = INT_MIN;
                j->price = INT_MIN;
                f = false;
                break;
            }
        }
        if (f) {
            ans += p;
        }
//        cout << i << " : " << ans << endl;

//        for (auto & j : q) {
//            cout << j.time << ':' << j.price << ' ';
//        } cout << endl;
    }
    cout << ans << endl;
    return 0;
}