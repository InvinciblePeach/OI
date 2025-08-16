//========================================== A ==========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, nums[205][205], cnt;
//
//int main() {
//    cin >> n;
//    for (int i = 1; i <= n; i ++) {
//        for (int j = 1; j <= n; j ++) {
//            cin >> nums[i][j];
//        }
//    }
//
//    for (int i = 1; i <= n; i ++) {
//        for (int j = 1; j <= n; j ++) {
//            bool flag = true;
//            for (int k = 1; k <= n; k ++) {
//                if (nums[i][k] != nums[k][j]) {
//                    flag = false;
//                    break;
//                }
//            }
//            if (flag) {
//                cnt ++;
//            }
//        }
//    }
//
//    cout << cnt << endl;
//
//    return 0;
//}
//========================================== B ==================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, cnt, nums[100005];
//
//int main() {
//    cin >> n;
//    bool zero = false;
//    for (int i = 1; i <= n; i ++) {
//        cin >> nums[i];
//        if (nums[i] == 0) {
//            zero = true;
//        }
//    }
//    if (!zero) {
//        cout << 0 << endl;
//        return 0;
//    }
//
//    for (int len = 0; len <= n; len ++) {
//        bool flag_1 = false;
//        for (int i = 1; i + len <= n; i ++) {
//            bool flag = true;
//            for (int j = i; j <= i + len; j ++) {
//                if (nums[j] != 0) {
//                    flag = false;
//                    break;
//                }
//            }
//            if (flag) {
//                flag_1 = true;
//                cnt ++;
//            }
//        }
//        if (!flag_1) {
//            break;
//        }
//    }
//    cout << cnt << endl;
//    return 0;
//}
//========================================== C ==========================================
#include <bits/stdc++.h>

using namespace std;

int cards[100005];
int n, m, diffs, nums[100005];

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie();
    cin.tie();

    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        cin >> nums[i];
    }

    for (auto i = 1; i <= n; i ++) {
        if (!cards[i]) {
            diffs ++;
            cards[i] ++;
        }
        if (diffs == n) {
            cout << 1;
            for (int i = 1; i <= m; i ++) {
                if (cards[i]--) {
                    diffs --;
                }
            }
        } else {
            cout << 0;
        }
    }

    cout << endl;
    return 0;
}
//========================================== D ==========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, k, rolls[100005];
//int dp[100005][100005];
//
//int main() {
//    cin >> n >> k;
//    for (int i = 1; i <= n; i ++) {
//        cin >> rolls[i];
//    }
//    for (int i = 1; i <= n; i ++) {
//        for (int j = 1; j <= n)
//    }
//    return 0;
//}
//========================================== E ==========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, m;
//int dp[65][35];
//
//int main() {
//    cin >> n >> m;
//    dp[1][n + 1] = 1;
//    for (int i = 1; i <= n * 2; i ++) {
//        dp[0][i] = dp[0][i - 1] + dp[0][i + 1];
//    }
//    for (int i = n * 2; i >= 1; i --) {
//        dp[0][i] = max(dp[0][i], dp[i - 1][j - 1], dp[i + 1][j - 1]);
//    }
//    for (int i = 1; i <= n * 2; i ++) {
//        for (int j = 1; j <= m; j ++) {
//            dp[i][j] = max(dp[i - 1][j - 1], dp[i + 1][j - 1]);
//        }
//    }
//    cout << dp[n][m] << endl;
//    return 0;
//}
//========================================== F ==========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//const int MOD = 998244353;
//int n, m, k;
//int dp[1005][1005], ans;
//
//int main() {
//    cin >> n >> m >> k;
//
//    if (k == 0) {
//        cout << m << endl;
//        return 0;
//    }
//
//    for (int i = 1; i <= n; i ++) {
//        for (int j = 0; j <= min(i - 1, k); j ++) {
//            if (i == 1) {
//                dp[i][0] = m;
//                continue;
//            }
//            dp[i][j] = dp[i - 1][j - 1] * (m - 1) + dp[i - 1][j];
//        }
//    }
//    cout << dp[n][k] << endl;
//    return 0;
//}