#include <bits/stdc++.h>

using namespace std;

int k, q, tot;
int trie[200005][26];
int next_[200005];
bool end_[200005];
string t;

void emplace(const string & s) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'a';
        if (!trie[root][tmp]) { trie[root][tmp] = ++ tot; }
        root = trie[root][tmp];
    }
    end_[root] = true;
}

void build() {
    queue<int> q; // NOLINT
    for (int i = 0; i < 26; i ++) {
        if (trie[0][i]) { q.emplace(trie[0][i]); }
    }
    while (!q.empty()) {
        int root = q.front();
        q.pop();
        for (int i = 0; i < 26; i ++) {
            if (!trie[root][i]) { trie[root][i] = trie[next_[root]][i]; }
            else {
                next_[trie[root][i]] = trie[next_[root]][i];
                q.emplace(trie[root][i]);
            }
        }
    }
}


int main() {
    cin >> k >> t >> q;
    for (int i = 1; i <= q; i ++) {
        string s;
        cin >> s;
        if (s.size() <= k) { cout << t.size() / s.size(); }
//        emplace(s);
    }
//    build();
    return 0;
}