#include <bits/stdc++.h>

using namespace std;

int T;
int n, cnt;
string s;
int next_k[1000005];

int main() {
    cin >> T;
    while (T --> 0) {
        memset(next_k, 0, sizeof(next_k));
        cin >> n;

        cin >> s;
        s = "S" + s; // NOLINT
        cnt ++;
        cout << "Test case #" << cnt << endl;

        int j = 0;
        for (int i = 2; i <= n; i ++) {
            while (j > 0 && s[i] != s[j + 1]) { j = next_k[j]; }

            if (s[i] == s[j + 1]) { j ++; }

            next_k[i] = j;
        }

        for (int i = 2; i <= n; i ++) {
            if (i % (i - next_k[i]) == 0 && i / (i - next_k[i]) > 1) {
                cout << i << ' ' << i / (i - next_k[i]) << endl;
            }
        }
        cout << endl;
    }
    return 0;
}