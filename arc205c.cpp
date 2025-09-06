#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10;
int n, cnt1, cnt2;
struct Node {
    int l, r, id;
} q1[MAXN], q2[MAXN];
vector<int> ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, s, t; i <= n; i++) {
        cin >> s >> t;
        if (s <= t)
            q1[++cnt1] = {s, t, i};
        else
            q2[++cnt2] = {t, s, i};
    }
    sort(q1 + 1, q1 + 1 + cnt1, [](Node a, Node b) { return a.l < b.l; });
    sort(q2 + 1, q2 + 1 + cnt2, [](Node a, Node b) { return a.r < b.r; });
    for (int i = 1, j = 0; i <= cnt1; i++) {
        while (j <= cnt2 && q2[j].r < q1[i].l) j++;
        // cerr << i << ' ' << j << '\n';
        if (q2[j].l < q1[i].l && q2[j].r > q1[i].l) return cout << "No\n", 0;
    }

    sort(q1 + 1, q1 + 1 + cnt1, [](Node a, Node b) { return a.r < b.r; });
    sort(q2 + 1, q2 + 1 + cnt2, [](Node a, Node b) { return a.l < b.l; });
    for (int i = 1, j = 0; i <= cnt2; i++) {
        while (j <= cnt1 && q1[j].r < q2[i].l) j++;
        // cerr << i << ' ' << j << '\n';
        if (q1[j].l < q2[i].l && q1[j].r > q2[i].l) return cout << "No\n", 0;
    }

    sort(q1 + 1, q1 + 1 + cnt1, [](Node a, Node b) { return a.r > b.r; });
    sort(q2 + 1, q2 + 1 + cnt2, [](Node a, Node b) { return a.l < b.l; });
    int l = INT_MAX, r = 0;
    for (int i = 1; i <= cnt1; i++) {
        ans.emplace_back(q1[i].id);
        if (l < q1[i].l) return cout << "No\n", 0;
        l = q1[i].l;
    }
    for (int i = 1; i <= cnt2; i++) {
        ans.emplace_back(q2[i].id);
        if (r > q2[i].r) return cout << "No\n", 0;
        r = q2[i].r;
    }
    cout << "Yes\n";
    for (auto v : ans) cout << v << ' ';
    cout << '\n';
    return 0;
}