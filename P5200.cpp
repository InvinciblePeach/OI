#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, a[MAXN], t[MAXN];

int lowbit(int x) { return x & -x; }

void add(int x, int val) {
    for (; x <= n; x += lowbit(x))
        t[x] += val;
}

int query(int x) {
    int res = 0;
    for (; x; x -= lowbit(x))
        res += t[x];
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int k = 0, len = n;
    for (; a[n - k - 1] < a[n - k]; k++, len--)
        add(a[n - k], 1);
    add(a[n - k], 1), len--;
    cout << len << '\n';
    for (int i = 1; i <= len; i++) {
        add(a[i], 1);
        cout << len - i + query(a[i] - 1) << " \n"[i == len];
    }
    return 0;
}