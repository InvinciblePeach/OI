#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
int n, m, p;
int sa[MAXN << 1], rk[MAXN << 1], id[MAXN], tmp[MAXN], cnt[MAXN];
string s;

signed main() {
    cin >> s;
    n = s.size(), m = 128;
    s = ' ' + s;
    for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i; i--) sa[cnt[rk[i]]--] = i;

    for (int len = 1; len < n; len <<= 1, m = p) {
        int cur = 0;
        for (int i = n - len + 1; i <= n; i++) id[++cur] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > len) id[++cur] = sa[i] - len;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) cnt[rk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i; i--) sa[cnt[rk[id[i]]]--] = id[i];

        p = 0;
        memcpy(tmp, rk, sizeof(tmp));
        for (int i = 1; i <= n; i++) {
            if (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + len] == tmp[sa[i - 1] + len])
                rk[sa[i]] = p;
            else
                rk[sa[i]] = ++p;
        }

        if (p == n) break;
    }

    for (int i = 1; i <= n; i++) cout << sa[i] << ' ';
    cout << endl;
    return 0;
}