// =========================================== A ===========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, num[105], cnt;
//
//int main() {
//    cin >> n;
//    for (int i = 0; i < n; i ++) { cin >> num[i]; }
//
//    sort(num, num + n);
//
//    int i = 0;
//    for (; i <= n; i ++) {
//        int tmp = num[i];
//        if (!tmp) {
//            cnt ++;
//            continue;
//        }
//        bool flag = true;
//        for (int j = i; j <= n; j ++) {
//            num[j] -= tmp;
//            if (num[j]) { flag = false; }
//        }
//        if (flag) {
//            break;
//        }
//    }
//    cout << i - cnt << endl;
//    return 0;
//}
// =========================================== B ===========================================
#include <bits/stdc++.h>

using namespace std;

int n, nums[100005], diff, cnt;

int main() {
    cin >> n >> diff;
    for (int i = 1; i <= n; i ++) { cin >> nums[i]; }

    int i = 1, j = 1, k = 1;
    for (; i <= n; i ++) {
        for (; j <= n; j ++) {
            if (nums[j] - nums[i] > diff) { break; }

            if (nums[j] - nums[i] == diff) {
                for (; k <= n; k ++) {
                    if (nums[k] - nums[j] > diff) { break; }

                    if (nums[k] - nums[j] == diff) {
                        cnt ++;
                        break;
                    }
                }
                break;
            }
        }
    }

    cout << cnt << endl;

    return 0;
}
// =========================================== C ===========================================
//#include <bits/stdc++.h>
//
//typedef long long LL;
//
//using namespace std;
//
//LL n, nums[100005], cnt;
//LL num[100005];
//
//int main() {
//    cin >> n;
//    for (int i = 0; i < n; i ++) { cin >> nums[i]; }
//    for (int i = 0; i < n; i ++) { num[i] = nums[i] - i; }
//
//    for (int i = 0; i < n; i ++) {
//        for (int j = i + 1; j < n; j ++) {
//            if (j - i != nums[j] - nums[i]) {
//                cnt ++;
//            }
//        }
//    }
//
//    cout << cnt << endl;
//
//    return 0;
//}
// =========================================== D ===========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int main() {
//    return 0;
//}
// =========================================== A ===========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n;
//
//int main() {
//    cin >> n;
//    for (int i = 1; i <= n; i ++) {
//        string s;
//        cin >> s;
//        s = "TJY AK IOI" + s; // NOLINT
//        if ((s[s.size() - 1] == '?') || (s[s.size() - 2] == 'A' && s[s.size() - 1] == 'K')) {
//            cout << "zqll" << endl;
//            continue;
//        } else if ((s[s.size() - 4] == 's' && s[s.size() - 3] == 'r' && s[s.size() - 2] == 'd' && s[s.size() - 1] == 's') ||
//        (s[s.size() - 4] == 'y' && s[s.size() - 3] == 'y' && s[s.size() - 2] == 's' && s[s.size() - 1] == 'y')) {
//            cout << "wtql" << endl;
//            continue;
//        } else if ((s[s.size() - 8] == 'd' && s[s.size() - 7] == 'a' && s[s.size() - 6] == 'l' && s[s.size() - 5] == 'a' && s[s.size() - 4] == 'o' && s[s.size() - 3] == '%' && s[s.size() - 2] == '%' && s[s.size() - 1] == '%') ||
//                  (s[s.size() - 3] == 't' && s[s.size() - 2] == 'q' && s[s.size() - 1] == 'l')) {
//            cout << "whra" << endl;
//            continue;
//        } else if ((s[s.size() - 3] == 'z' && s[s.size() - 2] == 't' && s[s.size() - 1] == 'o') ||
//                   (s[s.size() - 3] == 'o' && s[s.size() - 2] == 'r' && s[s.size() - 1] == 'z')) {
//            cout << "abaaba" << endl;
//            continue;
//        }
//    }
//    return 0;
//}
// =========================================== B ===========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, nums[100005];
//int cnt, score, num, now_score, now_num;
//
//int main() {
//    cin >> n;
//    for (int i = 1; i <= n; i ++) {
//        cin >> nums[i];
//    }
//
//    sort(nums + 1, nums + n + 1);
//
//    for (int i = 1; i <= n; i ++) {
//        now_num ++;
//        now_score += nums[i];
//        if (score < now_score && num < now_num) {
//            cnt ++;
//            score = now_score;
//            num = now_num;
//            now_score = 0;
//            now_num = 0;
//        }
//    }
//
//    cout << cnt << endl;
//
//    return 0;
//}
// =========================================== C ===========================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, m, nums[55][55];
//
//int main() {
//    cin >> n >> m;
//    for (int i = 1; i <= n; i ++) {
//        for (int j = 1; j <= n; j ++) {
//            cin >> nums[i][j];
//        }
//    }
//
//    for (int i = 1; i <= n - m + 1; i ++) {
//        for (int j = 1; j <= n - m + 1; j ++) {
//            int max_ = INT_MIN;
//            for (int l = i; l <= i + m - 1; l ++) {
//                for (int r = j; r <= j + m - 1; r ++) {
//                    max_ = max(max_, nums[l][r]);
//                }
//            }
//            cout << max_ << ' ';
//        }
//        cout << endl;
//    }
//
//    return 0;
//}
// =========================================== D ===========================================
//#include <bits/stdc++.h>
//#define minute_ second
//
//using namespace std;
//
//long long n, space, nums[100005], minute;
//map<long long, pair<bool, long long/*minute*/>> in_queue;
//
//int main() {
//    cin >> n >> space;
//    for (int i = 1; i <= n; i ++) { cin >> nums[i]; }
//
//    queue<pair<long long, long long>> q;
//
//    long long i = 1;
//    for (; i <= n;) {
//        while (!q.empty() && q.front().minute_ < minute - space) {
//            in_queue[q.front().first].first = false;
//            q.pop();
//        }
//
//        if (in_queue[nums[i]].first) {
//            minute = in_queue[nums[i]].minute_ + space;
//            continue;
//        }
//
//        q.emplace(nums[i], minute);
//        in_queue[nums[i]].first = true;
//        in_queue[nums[i]].minute_ = ++ minute;
//        i ++;
//    }
//
//    cout << minute << endl;
//
//    return 0;
//}