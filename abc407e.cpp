#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 4e5 + 10;
int T, n, a[MAXN];
priority_queue<int> q;
ll ans = 0;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        assert(q.empty());
        cin >> n;
        ans = 0;
        for (int i = 1; i <= (n << 1); i++)
            cin >> a[i], ans += a[i];

        for (int i = 1; i <= (n << 1); i++) {
            q.emplace(a[i]);
            if (q.size() > (i >> 1))
                q.pop();
        }

        while (!q.empty()) {
            ans -= q.top();
            q.pop();
        }

        cout << ans << "\n";
    }

    return 0;
}