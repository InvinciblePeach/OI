#include <bits/stdc++.h>

using namespace std;

int T, x, tmp, nxt[10000005];
bool check[10000005];

int main() {
    for (int i = 1; i <= 10000005; i ++) {
        if (check[i]) { continue; }
        if (to_string(i).find('7') != string::npos) {
            for (int j = i; j <= 10000005; j += i) {
                check[j] = true;
            }
            continue;
        }
        nxt[tmp] = i;
        tmp = i;
    }

    cin >> T;
    while (T --> 0) {
        cin >> x;
        if (check[x]) { cout << -1 << endl; }
        else {
            cout << nxt[x] << endl;
        }
    }
    return 0;
}