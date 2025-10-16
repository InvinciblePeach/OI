#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10;
int n, m = 128, p, cnt[MAXN], sa[MAXN], rk[MAXN], tmp[MAXN], id[MAXN], height[MAXN];
int st[MAXN], top, L[MAXN], R[MAXN];
ll ans;
string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s;
    n = s.size();
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
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 0) continue;
        if (k) k--;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) k++;
        height[rk[i]] = k;
    }
    st[top = 1] = 1;
    for (int i = 2; i <= n; ++i) {
        while (top && height[st[top]] > height[i]) R[st[top--]] = i;
        L[i] = st[top];
        st[++top] = i;
    }
    while (top) R[st[top--]] = n + 1;
    ans = ll(n - 1) * n * (n + 1) / 2;
    for (int i = 2; i <= n; ++i) ans -= 2ll * (R[i] - i) * (i - L[i]) * height[i];
    cout << ans << '\n';

    return 0;
}