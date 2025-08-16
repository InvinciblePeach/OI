#include <bits/stdc++.h>

using namespace std;

const long long border = 2147483648;

int a, n1, n2;
char c;
long long ans;

int main() {
    cin >> c >> c >> n1 >> c >> n2;

    if (c == '>') {
        ans += border - (n2 - n1 + 1) - n1;
    } else {
        ans += (n2 - n1 - 1) + border;
        if (border - n1 > n2) {
            ans += n1 + 1;
        } else {
            ans += border - n2;
        }
    }

    cout << ans << endl;
    return 0;
}