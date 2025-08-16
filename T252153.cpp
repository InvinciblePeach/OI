#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;
    for (auto i : s){
        if ('0' <= i && i <= '9') { // NOLINT
            cout << '9' - i;
        } else if ('a' <= i && i <= 'z') { // NOLINT
            cout << char(i - 32);
        } else {
            cout << char(i + 32);
        }
    }
    cout << endl;
    return 0;
}