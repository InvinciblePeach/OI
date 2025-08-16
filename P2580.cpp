#include <bits/stdc++.h>

using namespace std;

int n, m, tot;
int trie[5000005][26], cnt[5000005];
string change[] = {"WRONG", "OK", "REPEAT"}; // NOLINT

void insert(const string & s) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'a';
        if (!trie[root][tmp]) { trie[root][tmp] = ++ tot; }
        root = trie[root][tmp];
    }
    cnt[root] ++;
}

int query(const string & s) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'a';
        if (!trie[root][tmp]) { return 0; }
        root = trie[root][tmp];
    }
    return min(cnt[root] ++, 2);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        string s;
        cin >> s;
        insert(s);
    }

    cin >> m;
    for (int i = 1; i <= m; i ++) {
        string s;
        cin >> s;
        cout << change[query(s)] << endl;
    }
    return 0;
}