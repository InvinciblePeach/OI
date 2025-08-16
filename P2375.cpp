#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;
int next_k[1000005], num[1000005];
int n, l;
string s;

int main() {
    cin >> n;
    while (n-- > 0) {
        long long ans = 1;
        memset(next_k, 0, sizeof(next_k));
        memset(num, 0, sizeof(num));
        num[1] = 1;
        cin >> s;
        l = s.size();
        s = "s" + s; // NOLINT

        int k = 0;
        for (int i = 2; i <= l; i++) {
            while (k > 0 && s[i] != s[k + 1]) {
                k = next_k[k];
            }

            if (s[i] == s[k + 1]) {
                k++;
            }

            next_k[i] = k;
            num[i] = num[k] + 1;
        }

        int j = 0;
        for (int i = 2; i <= l; i++) {
            while (j > 0 && s[i] != s[j + 1]) {
                j = next_k[j];
            }

            if (s[i] == s[j + 1]) {
                j++;
            }

            while (j > i / 2) {
                j = next_k[j];
            }

            ans = ans * (long long)(num[j] + 1) % mod;
        }

        cout << ans << endl;
    }
    return 0;
}