#include <bits/stdc++.h>
#define int long long

using namespace std;

int T, p, a, b, x, t;
unordered_map<int, int> mp;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}

int inv(int x) { return qpow(x, p - 2); }

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int BSGS(int a, int b, int mod, int ad) {
    mp.clear();
    
    int s = ceil(sqrt(mod));
    int mul = 1;
    for (int i = 0; i < s; i++, (mul *= a) %= mod)
        mp[mul * b % mod] = i;
    int tmp = mul;
    mul = ad;
    for (int i = 0; i <= s; i++, (mul *= tmp) %= mod)
        if (mp.find(mul) != mp.end())
            if (i * s - mp[mul] >= 0)
                return i * s - mp[mul];
    return -1;
}

int exBSGS(int a, int b, int mod) {
    a %= mod, b %= mod;
    if (b == 1 || mod == 1) return 0;
    int cnt = 0;
    int d, ad = 1;
    while ((d = gcd(a, mod)) != 1) {
        if (b % d) return -1;
        cnt++, b /= d, mod /= d;
        (ad *= a / d) %= mod;
        if (ad == b) return cnt;
    }
    int res = BSGS(a, b, mod, ad);
    if (res != -1) return res + cnt;
    return -1;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> p >> a >> b >> x >> t;
        if (x == t) cout << "1\n";
        else if (a == 1) {
            t = ((t - x) % p + p) % p;
            if (t % gcd(b, p)) cout << "-1\n";
            else {
                if ((t * inv(b) + 1) % p == 0) cout << p << '\n';
                else cout << (t * inv(b) + 1) % p << '\n';
            }
        } else if (a == 0) {
            if (b == t) cout << "2\n";
            else cout << "-1\n";
        } else {
            int ans = exBSGS(a, ((t - b * inv(1 - a)) % p + p) % p * inv(((x - b * inv(1 - a)) % p + p) % p), p);
            if (~ans) cout << ans + 1 << '\n';
            else cout << "-1\n";
        }
    }

    return 0;
}