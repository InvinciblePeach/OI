#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n, q, a[MAXN], cnt[MAXN];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= q; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) {
        if (a[i]) {
            cnt[a[i]]++;
            cout << a[i] << " \n"[i == n];
        } else {
            int id = 0, mn = INT_MAX;
            for (int j = 1; j <= n; j++)
                if (cnt[j] < mn) id = j, mn = cnt[j];
            cout << id << " \n"[i == q];
            cnt[id]++;
        }
    }

    return 0;
}