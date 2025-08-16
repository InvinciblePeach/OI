#include <bits/stdc++.h>

using namespace std;

bool used[10];
string digits;
int n, ans, len;
int nums[] = {0,
              9,
              9 * 9,
              9 * 9 * 8,
              9 * 9 * 8 * 7,
              9 * 9 * 8 * 7 * 6,
              9 * 9 * 8 * 7 * 6 * 5,
              9 * 9 * 8 * 7 * 6 * 5 * 4,
              9 * 9 * 8 * 7 * 6 * 5 * 4 * 3,
              9 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2,
              };

int main() {
    cin >> n;
    len = digits.length();

    for (int i = 0; i < len; i ++) { ans += nums[i]; }

    for (int i = 0; i < len; i ++) {
        int cnt = 0;
        for (int j = !i; j < digits[len]; j ++) {
            if (used[digits[j]]) { continue; }
            cnt ++;
        }

        for (int j = i; j < len - 1; j ++) {
            cnt *= 9 - j;
        }

        ans += cnt;
        if (used[digits[i]]) { break; }
        used[digits[i]] = true;
    }

    cout << ans << endl;

    return 0;
}