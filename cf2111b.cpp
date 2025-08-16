#include<bits/stdc++.h>

using namespace std;

const int MAXN = 15;
int T, n, m, fib[MAXN];

bool check(int w, int l, int h) {
    vector<vector<int>> columns;

    for (int i = 1; i <= n; i++) {
        bool flag = false;
        for (auto &col : columns) {
            if (fib[i] <= col.back()) {
                int sum = 0;
                for (int e : col) sum += e;
                if (sum + fib[i] <= h) {
                    col.emplace_back(fib[i]);
                    flag = true;
                    break;
                }
            }
        }
        if (!flag) columns.emplace_back(vector<int>{fib[i]});
    }

    long long sum = 0;
    for (auto &col : columns)
        sum += col[0] * col[0];

    return sum <= w * l;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;

    while (T --> 0) {
        cin >> n >> m;
        fib[1] = 1, fib[2] = 2;
        for (int i = 2; i <= n; i++)
            fib[i] = fib[i - 1] + fib[i - 2];
        sort(fib + 1, fib + 1 + n, greater<>());

        while (m-- > 0) {
            static int w, l, h;
            cin >> w >> l >> h;
            if (check(w, l, h)) cout << 1;
            else cout << 0;
        }
        cout << '\n';
    }

    return 0;
}