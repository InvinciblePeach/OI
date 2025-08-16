#include <bits/stdc++.h>

using namespace std;

long long T;
long long l, r, x;

int main() {
    cin >> T;
    while (T --) {
        cin >> l >> r >> x;
        if (l / x == r / x) {
            cout << l / x << endl;
        } else {
            cout << 1 << endl;
        }
    }
    return 0;
}