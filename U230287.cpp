#include <bits/stdc++.h>

using namespace std;

int n, cnt;
string s;

bool check(int m) {
    int x = 0;
    for (; x < m; x ++) {
        if (s[x] != ' ' && s[x] == '#') { break; }
        else if (s[x] != ' ') { return false; }
    }

    if (s[++ x] != ' ') { return false; }

    for (; x < m; x ++) {
        if (s[x] != ' ') { return true; }
    }

    return false;
}

int main() {
    cin >> n;
    getline(cin, s);
    for (int i = 1; i <= n; i ++) {
        getline(cin, s);
        int m = s.size();

        for (int j = 0; j < m; j ++) {
            if (check(m)) {
                cnt ++;
                break;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}