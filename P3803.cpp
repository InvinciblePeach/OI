#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e7 + 10;
const double pi = acos(-1);
int n, m, rev[MAXN];

struct Complex {
    double x, y;

    Complex() {}
    Complex(double X, double Y) : x(X), y(Y) {}

    Complex operator+(const Complex &o) const { return {x + o.x, y + o.y}; }
    Complex operator-(const Complex &o) const { return {x - o.x, y - o.y}; }
    Complex operator*(const Complex &o) const {
        return {x * o.x - y * o.y, x * o.y + y * o.x};
    }
} A[MAXN], B[MAXN];

void fft(const int &len, Complex *a, const int &type) {
    for (int i = 1; i < len; i++)
        if (rev[i] > i) swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < len; mid <<= 1) {
        Complex Wn = {cos(pi / mid), type * sin(pi / mid)};
        for (int L = mid << 1, j = 0; j < len; j += L) {
            Complex w = {1, 0};
            for (int k = 0; k < mid; k++, w = Wn * w) {
                Complex p = a[j + k], q = w * a[j + k + mid];
                a[j + k] = p + q, a[j + k + mid] = p - q;
            }
        }
    }
}

void init(const int &len) {
    int d = len >> 1, p = 0;
    rev[p++] = 0;
    rev[p++] = d;
    for (int w = 2; w <= len; w <<= 1) {
        d >>= 1;
        for (int j = 0; j < w; j++)
            rev[p++] = rev[j] | d;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> A[i].x;
    for (int i = 0; i <= m; i++) cin >> A[i].y;
    int len = 1;
    while (len <= n + m) len <<= 1;
    init(len);
    fft(len, A, 1);
    for (int i = 0; i <= len; i++) A[i] = A[i] * A[i];
    fft(len, A, -1);
    for (int i = 0; i <= n + m; i++)
        cout << int(A[i].y / 2 / len + 0.5) << ' ';
    cout << '\n';

    return 0;
}