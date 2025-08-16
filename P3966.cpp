#include <bits/stdc++.h>

using namespace std;

int n, tot;
int trie[1000005][26], next_[1000005], ans[205];
bool end_[1000005];
vector<int> num[1000005];
string t;

void insert(const string & s, int i) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'a';
        if (!trie[root][tmp]) { trie[root][tmp] = ++ tot; }
        root = trie[root][tmp];
    }
    end_[root] = true;
    num[root].emplace_back(i);
}

void build() {
    queue<int> q;
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
    cin >> n;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        t.append(s + " ");
        insert(s, i);
    }

    build();

    int j = 0;
    for (auto c : t) {
        int tmp = c - 'a';
        j = trie[j][tmp];
        int now = j;
        while (now) {
            for (auto i : num[now]) { ans[i] ++; }
            now = next_[now];
        }
    }

    for (int i = 1; i <= n; i ++) { cout << ans[i] << endl; }
    return 0;
}