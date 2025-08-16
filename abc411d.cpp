#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;
int n, q, id;
int s, pos[MAXN];

struct Node {
    int pre;
    string val;
} t[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;

    while (q --> 0) {
        static int op, p;
        static string s;
        cin >> op >> p;

        if (op == 1) {
            pos[p] = ::s;
        } else if (op == 2) {
            string s;
            cin >> s;
            t[++id] = {pos[p], s};
            pos[p] = id;
        } else if (op == 3) {
            ::s = pos[p];
        }
    }

    vector<string> ans;
    int cur = s;
    while (cur != 0) {
        ans.emplace_back(t[cur].val);
        cur = t[cur].pre;
    }

    reverse(ans.begin(), ans.end());
    for (auto s : ans)
        cout << s;
    cout << '\n';


    return 0;
}