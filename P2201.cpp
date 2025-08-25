#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10;
int n, st1[MAXN], st2[MAXN], top1, top2, sum[MAXN], ans[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    ans[0] = INT_MIN;
    while (n --> 0) {
        static char c;
        static int x;
        cin >> c;
        if (c == 'I') {
            cin >> x;
            st1[++top1] = x;
            ans[top1] = max(ans[top1 - 1], sum[top1] = sum[top1 - 1] + x);
        } else if (c == 'D') {
            if (!top1) continue;
            top1--;
        } else if (c == 'L') {
            if (!top1) continue;
            st2[++top2] = st1[top1--];
        } else if (c == 'R') {
            if (!top2) continue;
            st1[++top1] = st2[top2--];
            ans[top1] = max(ans[top1 - 1], sum[top1] = sum[top1 - 1] + st1[top1]);
        } else if (c == 'Q') {
            cin >> x;
            cout << ans[x] << '\n';
        }
    }

    return 0;
}