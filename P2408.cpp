#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n;
ll ans;
string s;

namespace sam {
    int tot = 1, lst = 1;

    struct Node {
        int len, nxt;
        int v[26];
    } st[MAXN << 1];

    void add(int c) {
        int p = lst, np = lst = ++tot;
        st[np].len = st[p].len + 1;
        for (; p && !st[p].v[c]; p = st[p].nxt) st[p].v[c] = np;
        if (!p)
            st[np].nxt = 1;
        else {
            int q = st[p].v[c];
            if (st[q].len == st[p].len + 1)
                st[np].nxt = q;
            else {
                int nq = ++tot;
                st[nq] = st[q];
                st[nq].len = st[p].len + 1;
                st[q].nxt = st[np].nxt = nq;
                for (; p && st[p].v[c] == q; p = st[p].nxt) st[p].v[c] = nq;
            }
        }
        ans += st[np].len - st[st[np].nxt].len;
    }

    ll solve() {
        ll res = 0;
        for (int i = 2; i <= tot; i++) res += st[i].len - st[st[i].nxt].len;
        return res;
    }
} // namespace sam

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> s;
    for (int i = 0; i < n; i++) sam::add(s[i] - 'a');
    cerr << sam::tot << '\n';
    cout << ans << '\n';

    return 0;
}