#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 5e4 + 10;
int T, n, m, ans, mu[MAXN], f[MAXN];
bitset<MAXN> p;
vector<int> prime;

void init() {
	mu[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		if (!p[i]) {
			prime.emplace_back(i);
			mu[i] = -1;
		}

		for (auto j : prime) {
			if (i * j >= MAXN) break;
			p[i * j] = 1;
			if (!(i % j)) {
				mu[i * j] = 0;
				break;
			}
			mu[i * j] = -mu[i];
		}
	}
	for (int i = 1; i < MAXN; i++) mu[i] += mu[i - 1];
	for (int x = 1; x < MAXN; x++) {
		for (int l = 1, r; l <= x; l = r + 1) {
			r = x / (x / l);
			f[x] += (x / l) * (r - l + 1);
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	init();
	cin >> T;
	while (T --> 0) {
		cin >> n >> m;
		ans = 0;
		if (n > m) swap(n, m);
		for (int l = 1, r; l <= n; l = r + 1) {
			r = min(n / (n / l), m / (m / l));
			ans += (mu[r] - mu[l - 1]) * f[n / l] * f[m / l];
		}
		cout << ans << '\n';
	}
}