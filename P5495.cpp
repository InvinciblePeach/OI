#include <bits/stdc++.h>

using namespace std;

const uint MAXN = 2e7 + 10;
uint n, a[MAXN], ans, seed;
bitset<MAXN> p;
vector<int> prime;
 
inline uint getnext() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

void init() {
    for (int i = 2; i < MAXN; i++) {
        if (!p[i]) prime.emplace_back(i);
        
        for (auto j : prime) {
            if (i * j >= MAXN) break;
            p[i * j] = 1;
            if (!(i % j)) break;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> seed;
    for (int i = 1; i <= n; i++) a[i] = getnext();

    init();

    for (auto j : prime) {
        for (int i = 1; i * j <= n; i++) {
            a[i * j] += a[i];
        }
    }

    for (int i = 1; i <= n; i++) ans ^= a[i];
    cout << ans << '\n';

    return 0;
}