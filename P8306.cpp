#include <bits/stdc++.h>

using namespace std;

int T, n, q;
int trie[3000006][62], tot, cnt[3000005];

inline int ctoi(char c) {
    if (c >= 'a' && c <= 'z') { return c - 'a'; }
    else if (c >= 'A' && c <= 'Z') { return c - 'A' + 26; }
    else { return c - '0' + 52; }
}

inline void insert(const string & s) {
    int root = 0;
    for (auto c : s) {
        int node = ctoi(c);
        if (!trie[root][node]) { trie[root][node] = ++ tot; }

        root = trie[root][node];
        cnt[root] ++;
    }
}

inline int query(const string & s) {
    int root = 0;
    for (auto c : s) {
        int node = ctoi(c);
        if (!trie[root][node]) { return 0; }

        root = trie[root][node];
    }
    return cnt[root];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> T;
    while (T --> 0) {
        memset(trie, 0, (tot + 1) * 62 * 4);
        memset(cnt, 0, (tot + 1) * 4);
        tot = 0;

        cin >> n >> q;
        for (int i = 1; i <= n; i ++) {
            string s;
            cin >> s;
            insert(s);
        }
        for (int i = 1; i <= q; i ++) {
            string t;
            cin >> t;
            cout << query(t) << endl;
        }
    }
    return 0;
}