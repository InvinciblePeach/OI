#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

string p;
ll l;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> p >> l;
    if (p.size() >= l) cout << "Yes\n";
    else cout << "No\n";

    return 0;
}