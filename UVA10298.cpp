#include <bits/stdc++.h>

using namespace std;

int n, cnt;
int next_k[1000005];
string s;

int main() {
    while (true) {
        memset(next_k, 0, sizeof(next_k));
        cin >> s;
        if (s == ".") { break; }

        n = s.length();
        s = "S" + s; // NOLINT

        int j = 0;
        for (int i = 2; i <= n; i ++) {
            while (j > 0 && s[i] != s[j + 1]) { j = next_k[j]; }

            if (s[i] == s[j + 1]) { j ++; }

            next_k[i] = j;
        }

        cout << (n % (n - next_k[n]) == 0 ? (n / (n - next_k[n])) : 1) << endl;
    }
    return 0;
}