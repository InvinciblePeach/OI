#include <bits/stdc++.h>

using namespace std;

int T;

int main() {
    cin >> T;
    while (T --> 0) {
        string s;
        cin >> s;
        bool flag = true;

        if (s[0] == 'D' && s[1] == 'X') {
            cout << "Yes" << endl;
            continue;
        }

        for (int i = 0; i < s.size() - 3; i ++) {
            if (s[i] == s[i + 1] && s[i + 1] == s[i + 2] && s[i + 2] == s[i + 3]) {
                cout << "Yes" << endl;
                flag = false;
                break;
            }
        }

        if (flag) {
            cout << "No" << endl;
        }
    }
    return 0;
}