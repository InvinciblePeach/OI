#include <bits/stdc++.h>

using namespace std;

string s;
bool check[1000005];
stack<pair<char, int>> st; // NOLINT

int main() {
    cin >> s;
    for (int i = 0; i < s.size(); i ++) {
        if (!st.empty() && ((s[i] == ')' && st.top().first == '(') || (s[i] == ']' && st.top().first == '['))) {
            check[st.top().second] = check[i] = true;
            st.pop();
        } else {
            st.emplace(s[i], i);
        }
    }
//    for (int i = 0; i < s.size(); i ++) { cout << check[i] << ' '; }
//    cout << endl;
    int ans = INT_MIN, l, r, cnt = 0, now_l = 0, now_r = 0;
    for (int i = 0; i < s.size(); i ++) {
        if (check[i]) {
            cnt ++;
            now_r = i;
        } else {
            cnt = 0;
            now_l = i + 1;
        }

        if (cnt > ans) {
            ans = cnt;
            l = now_l;
            r = now_r;
        }
    }
    for (int i = l; i <= r; i ++) {
        cout << s[i];
    } cout << endl;
    return 0;
}