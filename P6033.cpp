#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e5 + 10;
int n, ans, cnt[MAXN];
queue<int> q1, q2;

int read() {
    char c = getchar();
    int res = 0, flag = 1;
    while (!isdigit(c)) {
        if (c == '-') flag = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res * flag;
}

int get() {
    int res;
    if (q1.size() && q2.size()) {
        if (q1.front() < q2.front()) res = q1.front(), q1.pop();
        else res = q2.front(), q2.pop();
    } else if (q1.size()) res = q1.front(), q1.pop();
    else if (q2.size()) res = q2.front(), q2.pop();
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    n = read();
    for (int i = 1; i <= n; i++)
        cnt[read()]++;
    for (int i = 1; i < MAXN; i++)
        while (cnt[i]--) q1.emplace(i);
    
    for (int i = 1; i < n; i++) {
        int x = get(), y = get();
        ans += x + y;
        q2.emplace(x + y);
    }
    cout << ans << '\n';

    return 0;
}