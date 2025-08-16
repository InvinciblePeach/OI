#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, lst;
unordered_set<string> s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for (n = 1; n <= 600; n++) {
        s.clear();
        for (int i = 1; i <= n; i++) {
            static string t;
            t = to_string(i) + to_string(i + 1);
            sort(t.begin(), t.end());
            s.emplace(t);
        }
        cout << n << '\t' << s.size() - lst << '\n';
        lst = s.size();
    }

    return 0;
}