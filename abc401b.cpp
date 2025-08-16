#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, cnt;
string s;
bool state;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    while (n --> 0) {
        cin >> s;
        if (s == "login") state = true;
        if (s == "logout") state = false;
        if (s == "private" && !state) cnt++;
    }
    cout << cnt << '\n';

    return 0;
}