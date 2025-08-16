#include <bits/stdc++.h>

using namespace std;

int n, next_k[1000005];
string s;

int main() {
    cin >> n >> s;
    s = "s" + s;

    int k = 0;
    for (int i = 2; i <= n; i ++) {
        while (k > 0 && s[i] != s[k + 1]) { k = next_k[k]; }

        if (s[i] == s[k + 1]) { k ++; }

        next_k[i] = k;
    }

    cout << n - next_k[n] << endl;
    return 0;
}