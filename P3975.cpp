#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10;
int n, T, k;
string s;

namespace sam {
    int tot = 1, lst = 1;
    ll siz[MAXN << 1], sum[MAXN << 1];
    int t[MAXN << 1], a[MAXN << 1];
    struct Node {
        int len, nxt;
        int v[26];
    } st[MAXN << 1];

    void add(int c) {
        int p = lst, np = lst = ++tot;
        st[np].len = st[p].len + 1;
        siz[np] = 1;
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
    }

    void out(int u, int k) {
        if (k <= siz[u]) return;
        k -= siz[u];
        for (int i = 0; i < 26; i++) {
            int v = st[u].v[i];
            if (!v) continue;
            if (k > sum[v]) {
                k -= sum[v];
                continue;
            }
            cout << char('a' + i);
            out(v, k);
            return;
        }
    }

    void solve() {
        for (int i = 1; i <= tot; i++) t[st[i].len]++;
        for (int i = 1; i <= tot; i++) t[i] += t[i - 1];
        for (int i = 1; i <= tot; i++) a[t[st[i].len]--] = i;
        for (int i = tot; i; i--) siz[st[a[i]].nxt] += siz[a[i]];
        memcpy(sum, siz, sizeof(sum));
        if (!T)
            for (int i = 1; i <= tot; i++) sum[i] = siz[i] = 1;
        sum[1] = siz[1] = 0;
        for (int i = tot; i; i--)
            for (int j = 0; j < 26; j++)
                if (st[a[i]].v[j]) sum[a[i]] += sum[st[a[i]].v[j]];
        if (sum[1] < k)
            cout << "-1\n";
        else
            out(1, k), cout << '\n';
    }
} // namespace sam

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s >> T >> k;
    for (auto c : s) sam::add(c - 'a');
    sam::solve();

    return 0;
}