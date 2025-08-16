#include <bits/stdc++.h>

using namespace std;

unordered_set<int> ans;
int k, n;
int rolls[100005];
int min_len = 1;

int main() {
    cin >> k >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> rolls[i];
    }
    for (int i = 1; i <= n; i ++) {
        ans.emplace(rolls[i]);
        if (ans.size() == k) {
            min_len ++;
            ans.clear();
        }
    }
    cout << min_len << endl;
    return 0;
}