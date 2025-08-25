#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10;
int n, b[MAXN], ans;

struct Node {
    int lc, rc;
    int val, dep;
} t[MAXN];

struct Node2 {
    int rt, l, r, siz, val;
} st[MAXN];
int top;

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (t[x].val < t[y].val) swap(x, y);
    t[x].rc = merge(t[x].rc, y);
    if (t[t[x].lc].dep < t[t[x].rc].dep) swap(t[x].lc, t[x].rc);
    t[x].dep = t[t[x].rc].dep + 1;
    return x;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    t[0].dep = -1;
    for (int i = 1; i <= n; i++) cin >> t[i].val, t[i].val -= i;
    for (int i = 1; i <= n; i++) {
        st[++top] = {i, i, i, 1, t[i].val};
        while (top != 1 && st[top - 1].val > st[top].val) {
            top--;
            st[top].rt = merge(st[top].rt, st[top + 1].rt);
            st[top].siz += st[top + 1].siz, st[top].r = st[top + 1].r;
            while (st[top].siz > ((st[top].r - st[top].l + 2) >> 1))
                --st[top].siz, st[top].rt = merge(t[st[top].rt].lc, t[st[top].rt].rc);
            st[top].val = t[st[top].rt].val;
        }
    }
    for (int i = 1, j = 1; i <= n; i++) {
        if (st[j].r < i) j++;
        ans += abs(st[j].val - t[i].val);
    }
    cout << ans << '\n';
    for (int i = 1, j = 1; i <= n; i++) {
        if (st[j].r < i) j++;
        cout << st[j].val + i << " \n"[i == n];
    }

    return 0;
}