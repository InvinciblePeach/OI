#include <bits/stdc++.h>

using namespace std;

int win, lose;
char s[700005];

int main() {
    for (int i = 1; s[i - 1] != 'E'; i ++) { cin >> s[i]; }

    for (auto i : s) {
        if (i == 'W') { win ++; }
        else if (i == 'L') { lose ++; }

        if ((win >= 11 || lose >= 11) && abs(win - lose) >= 2) {
            cout << win << ':' << lose << endl;
            win = 0, lose = 0;
        } else if (i == 'E') {
            cout << win << ':' << lose << endl;
            break;
        }
    }

    cout << endl;
    win = 0, lose = 0;

    for (auto i : s) {
        if (i == 'W') { win ++; }
        else if (i == 'L') { lose ++; }

        if ((win >= 21 || lose >= 21) && abs(win - lose) >= 2) {
            cout << win << ':' << lose << endl;
            win = 0, lose = 0;
        } else if (i == 'E') {
            cout << win << ':' << lose << endl;
            break;
        }
    }
    return 0;
}