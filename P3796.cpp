#include <bits/stdc++.h>

using namespace std;

int n, tot;
int trie[1000005][26], next_[1000005], ans[1000005], num[1000005];
bool cnt[1000005];
string str[200];
string t;

void insert(const string & s, int i) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'a';
        if (!trie[root][tmp]) { trie[root][tmp] = ++ tot; }
        root = trie[root][tmp];
    }
    cnt[root] = true, num[root] = i;
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
    while (cin >> n && n) {
        tot = 0;
        memset(ans, 0, sizeof(ans));
        memset(trie, 0, sizeof(trie));
        memset(cnt, 0, sizeof(cnt));
        memset(next_, 0, sizeof(next_));

        for (int i = 1; i <= n; i++) {
            cin >> str[i];
            insert(str[i], i);
        } cin >> t;

        build();

        int j = 0;
        for (auto c : t) {
            int tmp = c - 'a';
            j = trie[j][tmp];
            int now = j;
            while (now) {
                if (cnt[now]) { ans[num[now]] ++; }
                now = next_[now];
            }
        }

        int max_ = INT_MIN;
        for (int i = 1; i <= n; i ++) { max_ = max(max_, ans[i]); }
        cout << max_ << endl;
        for (int i = 1; i <= n; i ++) {
            if (ans[i] == max_) { cout << str[i] << endl;}
        }
    }
    return 0;
}