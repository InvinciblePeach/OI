#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;
int h, w, n, q, rcnt[MAXN], ccnt[MAXN];
vector<int> row[MAXN], col[MAXN];
bitset<MAXN> rvis, cvis;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> h >> w >> n;

    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        row[x].emplace_back(y);
        col[y].emplace_back(x);
        rcnt[x]++, ccnt[y]++;
    }

    cin >> q;
    while (q --> 0) {
        int op, k;
        cin >> op >> k;
        if (op == 1) {
            if (rvis[k]) {
                cout << "0\n";
            } else {
                cout << rcnt[k] << "\n";
                rvis[k] = 1;
                for (int y : row[k])
                    if (!cvis[y]) ccnt[y]--;
                rcnt[k] = 0;
            }
        } else {
            if (cvis[k]) {
                cout << "0\n";
            } else {
                cout << ccnt[k] << "\n";
                cvis[k] = 1;
                for (int x : col[k])
                    if (!rvis[x]) rcnt[x]--;
                ccnt[k] = 0;
            }
        }
    }

    return 0;
}