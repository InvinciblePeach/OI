#include <bits/stdc++.h>

using namespace std;

int n, q, cnt;
int p[100000005];
bool mark[100000005];

int main() {
    cin >> n >> q;

    for (int i = 2; i <= n; i ++) {
        mark[i] = true;
    }

    for (int i = 2; i <= n; i ++) {
        if (mark[i]) { P[++cnt] = i; }


        for (int j = 1; j <= cnt && i * P[j] <= n; j ++) {
            mark[i * P[j]] = false;
            if (i % P[j] == 0) { break; }
        }
    }

    for (int i = 1; i <= q; i ++) {
        int x;
        cin >> x;
        cout << P[x] << endl;
    }

    return 0;
}