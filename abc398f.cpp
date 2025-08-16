#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int n, nxt[MAXN], ans = 1;
string s, t;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s;
    n = s.size();
    t = s;
    reverse(s.begin(), s.end());
    s = ' ' + s, t = ' ' + t;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[i] != s[j + 1]) j = nxt[j];
        if (s[i] == s[j + 1]) j++;
        nxt[i] = j;
    }

    int j = 0;
    for (int i = 1; i <= n; i++) {
        while (j && t[i] != s[j + 1]) j = nxt[j];
        if (t[i] == s[j + 1]) j++;
    }
    ans = j;
    for (int i = n; i > ans; i--) cout << s[i];
    for (int i = 1; i <= n; i++) cout << s[i];

    return 0;
}