#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 60;
int n, m, mod, ans, inv[MAXN], frac[MAXN], invf[MAXN];
int n1, n2 = 1, st[MAXN], top;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

void dfs(int s, int mx, int c) {
    if (!s) return (ans += qpow(m, n1) * n2 % mod) %= mod, void();

    auto [a, b] = pair(n1, n2);
    for (int i = 1; i <= mx; i++) {
        st[++top] = i;
        n1 = a + (i >> 1);
        for (int j = 1; j < top; j++) n1 += gcd(st[j], i);
        n2 = b * inv[i] % mod;
        if (i == st[top - 1]) (n2 *= inv[c + 1] % mod) %= mod;
        dfs(s - i, min(s - i, i), (i == st[top - 1] ? c + 1 : 1));
        top--;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> mod;
    
	inv[1] = 1;
	for (int i = 2; i <= n + 1; ++i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    frac[0] = invf[0] = 1;
	for (int i = 1; i <= n + 1; ++i) {
		frac[i] = frac[i - 1] * i % mod;
		invf[i] = invf[i - 1] * inv[i] % mod;
	}
    dfs(n, n, 0);
    cout << ans << '\n';

    return 0;
}