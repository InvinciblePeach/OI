#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 110;
int n, sum;
string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int l;char c;
        cin >> c >> l;
        if ((sum += l) > 100) {
            cout << "Too Long\n";
            return 0;
        }
        s += string(l, c);
    }
    cout << s << '\n';

    return 0;
}