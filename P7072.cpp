#include <bits/stdc++.h>

using namespace std;

int n, w, now;
priority_queue<int, vector<int>, less<>> max_q; // NOLINT
priority_queue<int, vector<int>, greater<>> min_q; // NOLINT

int main() {
    cin >> n >> w;
    max_q.emplace(0);
    for (int i = 1; i <= n; i ++) {
        int x;
        cin >> x;
        now = max(1, i * w / 100);
        if (x <= max_q.top()) { max_q.emplace(x); }
        else { min_q.emplace(x); }

        while (min_q.size() < now) {
            min_q.emplace(max_q.top());
            max_q.pop();
        }
        while (min_q.size() > now) {
            max_q.emplace(min_q.top());
            min_q.pop();
        }
        cout << min_q.top() << ' ';
    } cout << endl;
    return 0;
}