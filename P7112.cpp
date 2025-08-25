#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 610;
int n, p, a[MAXN][MAXN];

int det(int mat[][MAXN]) {
    int res = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            while (mat[i][i]) {
                int t = mat[j][i] / mat[i][i];
                for (int k = i; k <= n; k++)
                    (mat[j][k] -= t * mat[i][k] % p) %= p;
                swap(mat[i], mat[j]), res = -res;
            }
            swap(mat[i], mat[j]), res = -res;
        }
        (res *= mat[i][i]) %= p;
    }
    return (res + p) % p;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> p;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    cout << det(a) << '\n';

    return 0;
}