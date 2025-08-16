#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s;
    for (auto a : s) {
        if ('A' <= a && a <= 'Z') cout << a;
    }
    cout << '\n';

    return 0;
}