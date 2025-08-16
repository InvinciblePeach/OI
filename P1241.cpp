#include <bits/stdc++.h>

using namespace std;

string s;
deque<char> st; // NOLINT
unordered_map<char, char> change = {{'(', ')'}, {'[', ']'}, {')', '('}, {']', '['}}; // NOLINT

int main() {
    cin >> s;
    for (auto i : s) {
        if (!st.empty()) {
            if ((i == ')' || i == ']') && st.back() == change[i]) {
                cout << st.back() << i;
                st.pop_back();
            }
            else { st.emplace_back(i); }
        } else { st.emplace_back(i); }
    }
    while (!st.empty()) {
        if (st.front() == '(' || st.front() == '[') { cout << st.front() << change[st.front()]; st.pop_front(); }
        else { cout << change[st.front()] << st.front(); st.pop_front(); }
    }
    return 0;
}