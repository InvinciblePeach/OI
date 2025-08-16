#include <bits/stdc++.h>

using namespace std;

int n, ans, tot;
int trie[1000005][26], cnt[1000005], next_[1000005];
string t;

void insert(const string & s) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'a';
        if (!trie[root][tmp]) { trie[root][tmp] = ++ tot; }
        root = trie[root][tmp];
    }
    cnt[root] ++;
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
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        string s;
        cin >> s;
        insert(s);
    } cin >> t;

    build();

    int j = 0;
    for (auto c : t) {
        int tmp = c - 'a';
        j = trie[j][tmp];
        int now = j;
        while (now && cnt[now]) {
            ans += cnt[now];
            cnt[now] = 0;
            now = next_[now];
        }
    }
    cout << ans << endl;
    return 0;
}