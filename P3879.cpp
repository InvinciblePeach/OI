#include <bits/stdc++.h>

using namespace std;

int n, m, l, tot;
int trie[500005][26];
bool end_[500005];
bitset<1005> cnt[500005];

void insert(const string & s, int i) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'a';
        if (!trie[root][tmp]) { trie[root][tmp] = ++ tot; }
        root = trie[root][tmp];
    }
    end_[root] = true, cnt[root][i] = true;
}

void query(const string & s) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'a';
        if (!trie[root][tmp]) { cout << " " << endl; return; }
        root = trie[root][tmp];
    }
    for (int i = 1; i <= n; i ++) {
        if (cnt[root][i]) { printf("%d ", i); }
    }
    puts("");
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> l;
        for (int j = 1; j <= l; j ++) {
            string s;
            cin >> s;
            insert(s, i);
        }
    }

    cin >> m;
    for (int i = 1; i <= m; i ++) {
        string s;
        cin >> s;
        query(s);
    }
    return 0;
}