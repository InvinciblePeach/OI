#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 15;
int a[MAXN], cnt[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for (int i = 1; i <= 7; i++) cin >> a[i], cnt[a[i]]++;
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 13; j++) {
            if (i == j) continue;
            if (cnt[i] >= 3 && cnt[j] >= 2) {
                cout << "Yes\n";
                return 0;
            }
        }
    }
    cout << "No\n";


    return 0;
}