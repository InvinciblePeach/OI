#include <bits/stdc++.h>

using namespace std;

int n, w, a[10000005];
int ans = 0;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    cin >> w;

    sort(a + 1, a + n + 1);

    w = *(upper_bound(a + 1, a + 1 + n, w) - 1);

    for (int i = 1; i <= n; i++){
        if (w < a[i]) {
            break;
        }
        w -= a[i];
        ans ++;
    }

    cout << ans << endl;

    return 0;
}