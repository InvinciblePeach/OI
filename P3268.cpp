#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef __int128 iit;

const iit mod = 7528443412579576937;
ll b, d, n;

struct Matrix {
    iit mtx[3][3];

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

    cin >> b >> d >> n;
    if (!n) return cout << "1\n", 0;
    iit tmp = iit(d >> 2) - iit((b + 1) >> 1) * ((b - 1) >> 1);
    Matrix base = Matrix();
    base.mtx[1][1] = b, base.mtx[2][1] = tmp, base.mtx[1][2] = 1;
    base = qpow(base, n - 1);
    iit ans = (base.mtx[1][1] * b + base.mtx[2][1] * 2) % mod;
    if (d != b * b && !(n & 1)) ans--;
    cout << ll((ans + mod) % mod) << '\n';

    return 0;
}