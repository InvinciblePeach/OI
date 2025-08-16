#include <bits/stdc++.h>

using namespace std;

int nums[] = {13, 1, 2, 3, 5, 4, 4, 2, 2, 2};

int T;
int k;
string n;

int main() {
    cin >> T;
    while (T --> 0) {
        cin >> n >> k;
        for (int i = 1; i <= k; i ++) {
            int cnt = 0;
            for (auto j : n) {
                cnt += nums[j - '0'];
            }
            n = to_string(cnt);
        }
        cout << n << endl;
    }
    return 0;
}