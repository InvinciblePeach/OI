#include <bits/stdc++.h>

using namespace std;

string s;
unordered_map<char, char> graph = {{'2', '5'}, {'5', '2'}, {'J', 'L'}, {'L', 'J'}}; // NOLINT

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> s;
    for (int i = int(s.length()) - 1; i >= 0; i --) {
        if (s[i] != '2' && s[i] != '5' && s[i] != 'J' && s[i] != 'L') { cout << s[i]; }
        else { cout << graph[s[i]]; }
    }
    cout << endl;
    return 0;
}