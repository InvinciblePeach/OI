#include <bits/stdc++.h>

using namespace std;

int m, n, i = 1;
int a[200005], u[200005];
priority_queue<int> main_q; // NOLINT;
priority_queue<int, vector<int>, greater<>> litter_q; // NOLINT

void check() {
    while (main_q.size() > i) {
        litter_q.emplace(main_q.top());
        main_q.pop();
    }
    while (main_q.size() < i) {
        main_q.emplace(litter_q.top());
        litter_q.pop();
    }
}

void emplace(int x) {
    if (x < main_q.top()) { main_q.emplace(x); }
    else { litter_q.emplace(x); }
    check();
}

int query() {
    check();
    i ++;
    return main_q.top();
}

int main() {
    cin >> n >> m;
    for (int j = 1; j <= n; j ++) { cin >> a[j]; }
    for (int j = 1; j <= m; j ++) { cin >> u[j]; }
    main_q.emplace(INT_MAX);
    for (int j = 1, tot = 1; j <= n && tot <= m; j ++) {
        emplace(a[j]);
        while (u[tot] == j) { cout << query() << endl; tot ++; }
    }
    return 0;
}