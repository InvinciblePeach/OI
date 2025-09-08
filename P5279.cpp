#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 4110, mod = 998244353, INF = 0x3f3f3f3f;
int n;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

struct Matrix {
    int a[3][3];
    int *operator[](const int &x) { return a[x]; }

    Matrix() { memset(a, -1, sizeof(a)); }

    bool operator<(Matrix b) const {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (a[i][j] ^ b[i][j]) return a[i][j] < b[i][j];
        return false;
    }

    bool operator!=(Matrix b) const {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (a[i][j] ^ b[i][j]) return true;
        return false;
    }

    void change(Matrix &o, int del) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (~a[i][j])
                    for (int k = 0, res = del - i - j; k < 3 && res >= 0; k++, res--)
                        o[j][k] = max(o[j][k], min(i + a[i][j] + res / 3, 4ll));
    }

    bool check() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (a[i][j] >= 4) return true;
        return false;
    }
};

struct Node {
    Matrix p[2];
    int cnt;
    bool operator<(const Node &o) const {
        if (cnt != o.cnt) return cnt < o.cnt;
        if (p[0] != o.p[0]) return p[0] < o.p[0];
        if (p[1] != o.p[1]) return p[1] < o.p[1];
        return false;
    }

    void clear() { p[0] = p[1] = Matrix(), cnt = -INF; }

    bool check() {
        if (cnt >= 7) return clear(), true;
        if (p[1].check()) return clear(), true;
        return false;
    }

    friend Node operator+(Node a, int x) {
        if (a.cnt == -INF) return a;
        Node res;
        if (x >= 2) a.p[0].change(res.p[1], x - 2);
        a.p[0].change(res.p[0], x);
        a.p[1].change(res.p[1], x);
        res.cnt = a.cnt + (x >= 2);
        res.check();
        return res;
    }
};

Node newnode() {
    Node res;
    res.clear(), res.cnt = 0, res.p[0][0][0] = 0;
    return res;
}

map<Node, int> id;
queue<Node> q;
int tot, g[MAXN][5], ed;

void bfs() {
    auto p = newnode();
    q.emplace(p);
    id[p] = ++tot;
    while (!q.empty()) {
        p = q.front();
        q.pop();
        auto u = id[p];
        for (int i = 0; i <= 4; i++) {
            auto tmp = p + i;
            if (id[tmp])
                g[u][i] = id[tmp];
            else
                g[u][i] = id[tmp] = ++tot, q.emplace(tmp);
        }
    }
    p.clear(), ed = id[p];
}

int frac[MAXN], invf[MAXN], cnt[110];
void init() {
    invf[0] = frac[0] = 1;
    for (int i = 1; i < MAXN; i++) frac[i] = frac[i - 1] * i % mod;
    invf[MAXN - 1] = inv(frac[MAXN - 1]);
    for (int i = MAXN - 2; i; i--) invf[i] = invf[i + 1] * (i + 1) % mod;
}

int C(int a, int b) { return frac[a] * invf[a - b] % mod * invf[b] % mod; }

int tmp1[410][MAXN], tmp2[410][MAXN];
void solve() {
    int nw = (n << 2) - 13;
    tmp1[0][1] = 1;
    for (int z = 1; z <= n; z++) {
        for (int i = nw; ~i; i--) {
            memset(tmp2[i], 0, sizeof(tmp2[i]));
            for (int j = 1; j <= tot; j++)
                if (tmp1[i][j])
                    for (int k = 0; k + cnt[z] <= 4 && i + k <= nw; k++)
                        (tmp2[i + k][g[j][k + cnt[z]]] += tmp1[i][j] * C(4 - cnt[z], k)) %= mod;
        }
        swap(tmp1, tmp2);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, p, x; i < 14; i++) {
        cin >> p >> x, cnt[p]++;
    }
    bfs(), init(), solve();
    // cerr << tot << '\n';
    int ans = 0;
    for (int p = 1, q = (n << 2) - 14; p <= (n << 2) - 13; p++, q--)
        for (int j = 1; j <= tot; j++)
            if (j ^ ed) (ans += tmp1[p][j] * frac[p] % mod * frac[q] % mod) %= mod;
    cout << ans * inv(frac[(n << 2) - 13]) % mod + 1 << '\n';
    return 0;
}