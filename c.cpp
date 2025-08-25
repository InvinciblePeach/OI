#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e4 + 10;
int C[MAXN][MAXN], st[MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    C[0][0] = 1;
    for (int i = 1; i <= 10; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }

    st[0][0] = 1;
    for (int i = 1; i <= 10; i++) {
        st[i][0] = 1;
        for (int j = 1; j <= i; j++)
            st[i][j] = j * st[i - 1][j] + st[i - 1][j - 1];
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j <= i; j++)
            cout << C[i][j] << ' ';
        cout << '\n';
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j <= i; j++)
            cout << st[i][j] << ' ';
        cout << '\n';
    }

    return 0;
}