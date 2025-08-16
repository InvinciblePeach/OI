#include <bits/stdc++.h>

using namespace std;

int T, n, w, a[10000005];
int ans = 0;

int main(){
    cin >> T;
    while (T --> 0) {
        ans = 0;
        cin >> n >> w;
        for (int i = 1; i <= n; i ++) { cin >> a[i]; }

        sort(a + 1, a + n + 1);

        for (int i = 1; i <= n; i ++) {
            if (w < a[i]) { break; }
            w -= a[i];
            ans ++;
        }

        cout << ans << endl;
    }
    return 0;
}