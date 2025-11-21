#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, X, Y, ans = INF;
struct Node {
    int a, b, c, d;
    bool operator<(const Node &o) const { return a < o.a; }
} t[MAXN];
vector<pii> tmp;
set<pii> odt;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> X >> Y >> n;
    odt.emplace(0, 0);
    for (int i = 1; i <= n; i++) {
        cin >> t[i].a >> t[i].b >> t[i].c >> t[i].d;
        if (t[i].a > t[i].c) swap(t[i].a, t[i].c);
        if (t[i].b > t[i].d) swap(t[i].b, t[i].d);
        t[i].b--, t[i].d++;
    }
    sort(t + 1, t + 1 + n);
    for (int i = 1; i <= n && t[i].a <= X; i++) {
        if (t[i].a ^ t[i - 1].a) {
            for (auto j : tmp) odt.emplace(j);
            tmp.clear();
        }
        int mn1 = INF, mn2 = INF;
        auto it1 = odt.lower_bound({t[i].b, 0}), it2 = it1;
        for (; it2 != odt.end() && it2->first <= t[i].d; it2++)
            mn1 = min(mn1, it2->second + abs(t[i].b - it2->first)),
            mn2 = min(mn2, it2->second + abs(t[i].d - it2->first));
        tmp.emplace_back(t[i].b, mn1);
        tmp.emplace_back(t[i].d, mn2);
        odt.erase(it1, it2);
    }
    for (auto j : tmp) odt.emplace(j);
    for (auto j : odt) ans = min(ans, j.second + abs(Y - j.first));
    cout << ans + X << '\n';

    return 0;
}