#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 10;
int T, n, q, ans, tot, bk[MAXN];
string s;
struct node {
    int ch[70];
    int cnt;
    bool ed;
    bool flag;
} t[MAXN];

inline int change(char c) {
    if (c <= 'z' && c >= 'a') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 36;
    } else return c - '0';
}

void Insert(string s) {
    int tmp = 1;
    for (auto c : s) {
        if (!t[tmp].ch[change(c)]) t[tmp].ch[change(c)] = ++tot;
        tmp = t[tmp].ch[change(c)];
    }
    t[tmp].flag = true;
    ans -= t[tmp].cnt;
}

void tag(string s) {
    int tmp = 1;
    bool flag = true;
    for (auto c : s) {
        if (!t[tmp].ch[change(c)]) t[tmp].ch[change(c)] = ++tot;
        tmp = t[tmp].ch[change(c)];
        if (t[tmp].flag) flag = false;
    }
    tmp = 1;
    for (auto c : s) {
        tmp = t[tmp].ch[change(c)];
        t[tmp].cnt += flag;
    }
    ans += flag;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> q;
    while (q --> 0) {
        static int op;
        cin >> op >> s;
        if (op == 1) {
            Insert(s);
        } else {
            tag(s);
        }
        cout << ans << '\n';
    }
    return 0;
}