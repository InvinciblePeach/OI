#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n, rk[MAXN];

struct Node {
    int id, val;

    Node() {}
    Node(int Id, int Val) : id(Id), val(Val) {}

    bool operator<(const Node &o) const { return val > o.val; }
} p[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i].val, p[i].id = i;
    sort(p + 1, p + 1 + n);
    for (int i = 1, j = 1, k = 0; i <= n; i++, j++) {
        if (p[i].val != p[i - 1].val) k = j;
        rk[p[i].id] = k;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        cout << rk[i] << '\n';
    }

    return 0;
}