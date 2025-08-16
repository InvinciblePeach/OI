#include <bits/stdc++.h>

using namespace std;

int n, m, cnt;
priority_queue<int> max_q; // NOLINT
priority_queue<int, vector<int>, greater<>> min_q; // NOLINT

void check() {
    int mid = !(cnt % 2) ? (cnt / 2) : (cnt / 2 + 1);
    while (max_q.size() < mid) {
        max_q.emplace(min_q.top());
        min_q.pop();
    }
    while (max_q.size() > mid) {
        min_q.emplace(max_q.top());
        max_q.pop();
    }
}

void emplace(int x) {
    if (x < max_q.top()) { max_q.emplace(x); }
    else { min_q.emplace(x); }
    cnt ++;
    check();
}

int main() {
    cin >> n;
    max_q.emplace(INT_MAX);
    min_q.emplace(INT_MAX);
    for (int i = 1; i <= n; i ++) {
        int num;
        cin >> num;
        emplace(num);
        if (i % 2) { cout << max_q.top() << endl; }
    }
    return 0;
}