#include <bits/stdc++.h>

using namespace std;

int n, k;
int a[100005];

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    deque<int> dq;
    for (int i = 0; i < n; i ++) {
        if (dq.front() <= i - k) {
            dq.pop_front();
        }

        while (!dq.empty()) {
            if (a[dq.back()] >= a[i]) {
                dq.pop_back();
            } else {
                dq.push_back(i);
                break;
            }
        }
        if (dq.empty()) {
            dq.push_back(i);
        }

        if (i >= k - 1) {
            cout << a[dq.front()] << ' ';
        }
    }

    cout << endl;
    dq.clear();

    for (int i = 0; i < n; i ++) {
        if (dq.front() <= i - k) {
            dq.pop_front();
        }

        while (!dq.empty()) {
            if (a[dq.back()] <= a[i]) {
                dq.pop_back();
            } else {
                dq.push_back(i);
                break;
            }
        }
        if (dq.empty()) {
            dq.push_back(i);
        }

        if (i >= k - 1) {
            cout << a[dq.front()] << ' ';
        }
    }
    return 0;
}
