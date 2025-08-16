#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10, INF = 0x3f3f3f3f;
int T, n, ans, w[MAXN], a[MAXN], b[MAXN], c[MAXN], suma[MAXN], sumb[MAXN], sumc[MAXN], posb[MAXN], posc[MAXN], f[MAXN];

struct Node {
    int l, r;
    int lmx, rmx;
    int mx, tag;

    void entag(int val) { lmx = rmx = tag = val, mx = sumb[r] + val; }
} t[MAXN << 2];

void pushup(int p) { t[p].lmx = t[lc(p)].lmx, t[p].rmx = t[rc(p)].rmx, t[p].mx = max(t[lc(p)].mx, t[rc(p)].mx); }

void pushdown(int p) {
    int &tag = t[p].tag;
    if (~tag) t[lc(p)].entag(tag), t[rc(p)].entag(tag), tag = -1;
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r, t[p].tag = -1;
    if (l == r) return t[p].lmx = t[p].rmx = f[l], t[p].mx = f[l] + sumb[l], void();
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int pos, int val) {
    if (pos <= t[p].l) {
        if (val >= t[p].lmx) return;
        if (val < t[p].rmx) return t[p].entag(val);
    }
    pushdown(p);
    if (pos <= t[lc(p)].r) modify(lc(p), pos, val);
    modify(rc(p), pos, val);
    pushup(p);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    char C;
    cin >> C >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> w[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i], posb[b[i]] = i;
        for (int i = 1; i <= n; i++) cin >> c[i], posc[c[i]] = i;
        for (int i = 1; i <= n; i++) cin >> suma[i], suma[i] += suma[i - 1];
        for (int i = 1; i <= n; i++) cin >> sumb[i], sumb[i] += sumb[i - 1];
        for (int i = 1; i <= n; i++) cin >> sumc[i], sumc[i] += sumc[i - 1];

        f[0] = sumc[n];
        for (int i = 1; i <= n; i++) {
            f[i] = f[i - 1];
            if (w[b[i]] == 1) f[i] = min(f[i], sumc[posc[b[i]] - 1]);
        }

        build(1, 0, n);
        ans = t[1].mx;
        for (int i = 1; i <= n; i++) {
            if (w[a[i]] == 1)
                modify(1, posb[a[i]], -INF), modify(1, 0, sumc[posc[a[i]] - 1]);
            else
                modify(1, posb[a[i]], sumc[posc[a[i]] - 1]);
            ans = max(ans, suma[i] + t[1].mx);
        }
        cout << ans << '\n';
    }

    return 0;
}