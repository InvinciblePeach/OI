#include <bits/stdc++.h>

using namespace std;

int cards[100005];
int n, m, diffs, nums[100005];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        cin >> nums[i];
    }

    for (int i = 1; i <= m; i ++) {
        if (!cards[nums[i]]) {
            diffs ++;
            cards[nums[i]] ++;
        } else {
            cards[nums[i]] ++;
        }

        if (diffs == n) {
            cout << '1';
            for (int j = 1; j <= n; j ++) {
                if (!(-- cards[j])) { diffs --;}
            }x
        } else { cout << '0';}
    }

    cout << endl;
    return 0;
}