#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10, mod = 998244353;
int n, m;
string s;

constexpr int lc(int p) { return p << 1; }
constexpr int rc(int p) { return p << 1 | 1; }

struct Matrix {
    int a[3][3];

    Matrix() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                a[i][j] = 0;
    }

    void init() {
        for (int i = 0; i < 3; i++)
            a[i][i] = 1;
    }

    Matrix operator*(const Matrix &o) {
        Matrix res;
        for (int i = 0; i < 3; i++)
            for (int k = 0; k < 3; k++)
                for (int j = 0; j < 3; j++)
                    (res.a[i][j] += a[i][k] * o.a[k][j]) %= mod;
        return res;
    }
} m0, m1, ma;

struct Node {
    int l, r;
    Matrix tag;
} t[MAXN << 2];

void pushup(int p) { t[p].tag = t[lc(p)].tag * t[rc(p)].tag; }

void build(int p, int l, int r) { 
    t[p] = {l, r};
    if (l == r) {
        if (s[l] == '0') t[p].tag = m0;
        else if (s[l] == '1') t[p].tag = m1;
        else if (s[l] == '?') t[p].tag = ma;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int x) {
    if (t[p].l == t[p].r) {
        if (s[t[p].l] == '0') t[p].tag = m0;
        else if (s[t[p].l] == '1') t[p].tag = m1;
        else if (s[t[p].l] == '?') t[p].tag = ma;
        return;
    }
    if (x <= t[lc(p)].r) modify(lc(p), x);
    else modify(rc(p), x);
    pushup(p);
}

Matrix query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].tag;
    Matrix res;
    if (l <= t[lc(p)].r) res = res * query(lc(p), l, r);
    if (r >= t[rc(p)].l) res = res * query(rc(p), l, r);
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    {
        m0.a[0][0] = 1, m0.a[0][1] = 1, m0.a[0][2] = 1;
        m0.a[1][0] = 0, m0.a[1][1] = 1, m0.a[1][2] = 0;
        m0.a[2][0] = 0, m0.a[2][1] = 0, m0.a[2][2] = 1;
    }
    {
        m1.a[0][0] = 1, m1.a[0][1] = 0, m1.a[0][2] = 0;
        m1.a[1][0] = 1, m1.a[1][1] = 1, m1.a[1][2] = 1;
        m1.a[2][0] = 0, m1.a[2][1] = 0, m1.a[2][2] = 1;
    }
    {
        ma.a[0][0] = 1, ma.a[0][1] = 1, ma.a[0][2] = 1;
        ma.a[1][0] = 1, ma.a[1][1] = 1, ma.a[1][2] = 1;
        ma.a[2][0] = 0, ma.a[2][1] = 0, ma.a[2][2] = 1;
    }

    cin >> n >> m >> s;
    s = ' ' + s;
    build(1, 1, n);
    while (m --> 0) {
        static int x;
        static char c;
        cin >> x >> c;
        s[x] = c;
        modify(1, x);
        auto ans = query(1, 1, n);
        cout << (ans.a[0][2] + ans.a[1][2]) % mod << '\n';
    }

    return 0;
}