#include <bits/stdc++.h>

using namespace std;

int n, cnt;
int power[40];

int main() {
    cin >> n;
    if (n % 2) { cout << -1 << endl; return 0; }
    for (int i = 1; i <= n; i *= 2, cnt ++) { power[cnt] = i; }
    cnt --;
    for (; power[cnt] > 1; cnt --) {
        if (n >= power[cnt]) {
            cout << power[cnt] << ' ';
            n -= power[cnt];
        }
    }
    return 0;
}