#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll mod = 998244353;
ll t, n;

struct Matrix {
    ll mtx[3][3];

    Matrix() { memset(mtx, 0, sizeof(mtx)); }

    Matrix operator*(const Matrix &o) {
        Matrix res = Matrix();
        for (int i = 1; i <= 2; i++)
            for (int k = 1; k <= 2; k++)
                for (int j = 1; j <= 2; j++)
                    (res.mtx[i][j] += mtx[i][k] * o.mtx[k][j] % mod) %= mod;
        return res;
    }
};

Matrix qpow(Matrix b, ll x) {
    Matrix res = Matrix();
    res.mtx[1][1] = res.mtx[2][2] = 1;
    while (x) {
        if (x & 1) res = res * b;
        b = b * b;
        x >>= 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        cin >> n;
        if (n == 0) {
            cout << "1\n";
            continue;
        }
        if (n == 1) {
            cout << "2\n";
            continue;
        }
        Matrix base = Matrix();
        base.mtx[1][1] = 1, base.mtx[2][1] = 1, base.mtx[1][2] = 1;
        base = qpow(base, n - 2);
        ll ans = (base.mtx[1][1] * 3 + base.mtx[2][1]) % mod;
        if (n & 1) ans++;
        cout << (ans + mod) % mod << '\n';
    }

    return 0;
}