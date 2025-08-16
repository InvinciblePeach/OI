#include <bits/stdc++.h>

using namespace std;

int n, tot;
int trie[100005][30];

void emplace(const string & s) {
    int root = 0;
    for (auto c : s) {
        int tmp = c - 'A';
        if (!trie[root][tmp]) { trie[root][tmp] = ++ tot; }
        root = trie[root][tmp];
    }61
}

int main() {
    string s;
    while (cin >> s) { emplace(s); }
    cout << tot + 1 << endl;
    return 0;
}