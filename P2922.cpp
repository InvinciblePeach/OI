#include <bits/stdc++.h>

using namespace std;

int n, m, tot;
int trie[500005][2], cnt[500005], end_[500005];

void insert(const string & s) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - '1';
        if (!trie[root][tmp]) { trie[root][tmp] = ++ tot; }
        root = trie[root][tmp];
        cnt[root] ++;
    }
    end_[root] ++;
}

int query(const string & s) {
    int counter = 0;
    int root = 0;
    for (auto c : s) {
        int tmp = c - '1';
        if (!trie[root][tmp]) { return counter; }
        root = trie[root][tmp];
        counter += end_[root];
    }
    return counter - end_[root] + cnt[root];
}

int main() {
    cin >> m >> n;
    for (int i = 1; i <= m; i ++) {
        int len;
        string s;
        cin >> len;
        for (int j = 1; j <= len; j ++) {
            char c;
            cin >> c;
            s += c;
        }
        insert(s);
    }

    for (int i = 1; i <= n; i ++) {
        int len;
        string s;
        cin >> len;
        for (int j = 1; j <= len; j ++) {
            char c;
            cin >> c;
            s += c;
        }
        cout << query(s) << endl;
    }

    return 0;
}