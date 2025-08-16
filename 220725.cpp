// ============================================ A ===============================================
#include <bits/stdc++.h>

using namespace std;

int M, D, ans = 0;
int month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    scanf("%d-%d", & M, & D); // NOLINT

    if (M > 12) {
        ans ++;
    }

    if (D > month[M % 10]) {
        ans ++;
    }

    if (M > 12 && M % 10 <= 2 && D <= month[M % 10 + 10] && ans > 1) {
        ans = 1;
    }

    cout << ans << endl;

    return 0;
}
// ============================================ B ===============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n;
//string persons[105];
//string s[105];
//
//int main() {
//    cin >> n;
//
//    long long max_ = INT_MIN;
//    string max_person;
//
//    for (int i = 1; i <= n; i++) {
//        cin >> persons[i];
//        cin >> s[i];
//
//        long long ans = 0;
//
//        for (int j = 0; j < s[i].size(); j++) {
//            if (j + 2 < s[i].size()) {
//                if (s[i][j] == 's' && s[i][j + 1] == 'o' && s[i][j + 2] == 's') {
//                    ans ++;
//                }
//            }
//        }
//        if (ans > max_){
//            max_ = ans;
//            max_person = persons[i] + " ";
//        } else if (ans == max_) {
//            max_person += persons[i] + " ";
//        }
//    }
//
//    cout << max_person << endl << max_ << endl;
//
//    return 0;
//}
// ============================================ C ===============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//
//int n;
//pair<int, string> a[100005]; // NOLINT
//
//int main() {
//    cin >> n;
//    for (int i = 1; i <= n; i++) {
//        cin >> a[i].second;
//    }
//
//    for (int i = 1; i <= n; i++) {
//        for (auto j : a[i].second) {
//            a[i].first += j - '0';
//        }
//    }
//
//    sort(a + 1, a + 1 + n, greater<>());
//
//    int ans = -1;
//
//    for (int i = 1; i < n; i++) {
//        if (a[i].first == a[i + 1].first) {
//            ans = max(stoi(a[i].second) + stoi(a[i + 1].second), ans);
//        }
//    }
//
//    cout << ans << endl;
//
//    return 0;
//}
// ============================================ D ===============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, m, gcd;
//int nums[100005], numsDivide[100005];
//
//int main() {
//    cin >> n >> m;
//
//    for (int i = 1; i <= n; i++) {
//        cin >> nums[i];
//    }
//
//    for (int i = 1; i <= m; i++) {
//        cin >> numsDivide[i];
//    }
//
//    sort(nums + 1, nums + 1 + n);
//
//    gcd = numsDivide[1];
//
//    for (int i = 2; i <= n; i++) {
//        while (numsDivide[i] % gcd != 0) {
//            gcd--;
//        }
//    }
//
//    for (int i = 1; i <= n; i ++) {
//        if (gcd % nums[i] == 0) {
//            cout << i - 1 << endl;
//            return 0;
//        }
//    }
//
//    cout << -1 << endl;
//
//    return 0;
//}
// ============================================ E ===============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, k, dp[1005][1005];
//
//int main() {
//    cin >> n >> k;
//
//    if (k > n) {
//        cout << 0 << endl;
//        return 0;
//    } else if (k == n) {
//        cout << 1 << endl;
//        return 0;
//    }
//
//    for (int i = 0; i <= n; i++) {
//        dp[i][0] = 1;
//    }
//    for (int i = 1; i <= k; i++) {
//        dp[0][i] = 0;
//    }
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= k; j++) {
//            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % 10000;
//        }
//    }
//    cout << dp[n][k] % 10000 << endl;
//    return 0;
//}