#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

string s, t;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s >> t;
    auto find = [=](char c) -> bool {
        for (auto v : t) if (v == c) return true;
        return false;
    };
    bool flag = true;
    for (int i = 1; i < s.size(); i++) {
        if ('A' <= s[i] && s[i] <= 'Z') if (!find(s[i - 1])) flag = false;
    }
    cout << (flag ? "Yes\n" : "No\n");

    return 0;
}