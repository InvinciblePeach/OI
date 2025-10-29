#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int T, n, ans, cnt10[MAXN], cnt20[MAXN], cnt11[MAXN], cnt21[MAXN];
string s1, s2, t1, t2;

struct DSU {
    int fa[MAXN];
    void init() {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }
    int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
    void merge(int x, int y) { fa[get(x)] = get(y); }
} a1, a2;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n;
        cin >> s1 >> s2 >> t1 >> t2;
        s1 = ' ' + s1, s2 = ' ' + s2, t1 = ' ' + t1, t2 = ' ' + t2;
        ans = 0;
        a1.init(), a2.init();
        for (int i = 1; i <= n; i++)
            if (t1[i] == '0' && t1[i - 1] == '0') a1.merge(i, i - 1);
        for (int i = 1; i <= n; i++)
            if (t2[i] == '0' && t2[i - 1] == '0') a2.merge(i, i - 1);
        for (int i = 1; i <= n; i++) cnt10[a1.get(i)] += '1' - s1[i], cnt11[a1.get(i)] += s1[i] - '0';
        for (int i = 1; i <= n; i++) cnt20[a2.get(i)] += '1' - s2[i], cnt21[a2.get(i)] += s2[i] - '0';
        for (int i = 1; i <= n; i++) {
            if (t1[i] == '0') {
                int x = a1.get(i), y = a2.get(i);
                int tmp0 = min(cnt10[x], cnt20[y]);
                cnt10[x] -= tmp0, cnt20[y] -= tmp0, ans += tmp0;
                int tmp1 = min(cnt11[x], cnt21[y]);
                cnt11[x] -= tmp1, cnt21[y] -= tmp1, ans += tmp1;
                if (cnt10[x]) cnt21[y] -= cnt10[x];
                if (cnt11[x]) cnt20[y] -= cnt11[x];
            } else if (t2[i] == '0') {
                int x = a1.get(i), y = a2.get(i);
                int tmp0 = min(cnt10[x], cnt20[y]);
                cnt10[x] -= tmp0, cnt20[y] -= tmp0, ans += tmp0;
                int tmp1 = min(cnt11[x], cnt21[y]);
                cnt11[x] -= tmp1, cnt21[y] -= tmp1, ans += tmp1;
                if (cnt10[x]) cnt21[y] -= cnt10[x];
                if (cnt11[x]) cnt20[y] -= cnt11[x];
            }
        }
    }

    return 0;
}