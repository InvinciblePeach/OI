#include <bits/stdc++.h>

using namespace std;

int n, m, next_k[1000005];
string s, p;

int main() {
    cin >> s >> p;
    n = s.size(), m = p.size();
    s = "s" + s, p = "p" + p;

    int j = 0;
    for (int i = 2; i <= m; i ++) {
        while (j > 0 && p[i] != p[j + 1]) { j = next_k[j]; }

        if (p[i] == p[j + 1]) { j ++; }

        next_k[i] = j;
    }

    int k = 0;
    for (int i = 1; i <= n; i ++) {
        while (k > 0 && s[i] != p[k + 1]) { k = next_k[k]; }

        if (s[i] == p[k + 1]) { k ++; }

        if (k + 1 == m + 1) { cout << i - m + 1 << endl; k = next_k[k]; }
    }

    for (int i = 1; i <= m; i ++) { cout << next_k[i] << ' '; }

    cout << endl;

    return 0;
}