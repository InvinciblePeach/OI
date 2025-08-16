// ==================================== A ====================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, k, cnt, ans = INT_MAX;
//string s;
//char c;
//queue<char> q; // NOLINT
//
//int main() {
//    cin >> n >> k >> c;
//    cin >> s;
//    for (int i = 0; i < k; i ++) {
//        q.emplace(s[i]);
//        if (s[i] != c) { cnt ++; }
//    }
//
//    ans = cnt;
//    for (int i = k; i < n; i ++) {
//        auto tmp = q.front();
//        q.pop();
//        q.emplace(s[i]);
//        if (s[i] != c) { cnt ++; }
//        if (tmp != c) { cnt --; }
//        ans = min(cnt, ans);
//    }
//
//    cout << ans << endl;
//
//    return 0;
//}
// ==================================== B ====================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, nums[100005], cnt[10], mid;
//string ans;
//
//int main() {
//    cin >> n;
//    for (int i = 1; i <= n; i ++) {
//        cin >> nums[i];
//        cnt[nums[i]] ++;
//    }
//
//    for (int i = 9; i >= 0; i --) {
//        if (cnt[i] >= 2) {
//            for (int j = 1; j <= cnt[i] / 2; j ++) {
//                ans = ans + to_string(i); // NOLINT
//            }
//        }
//        if (cnt[i] && cnt[i] % 2 != 0) { mid = max(mid, i); }
//    }
//
//    bool is_all_zero = true;
//    if (ans.empty()) { cout << mid; return 0; }
//    for (auto i : ans) {
//        if (i != '0') { is_all_zero = false; break; }
//    }
//    if (is_all_zero) { cout << mid; return 0; }
//    cout << ans;
//    cout << mid;
//    for (auto i = ans.rbegin(); i != ans.rend(); i ++) {
//        cout << *i;
//    }
//    cout << endl;
//
//    return 0;
//}
// ==================================== C ====================================
// ==================================== D ====================================
// ==================================== Div.2 ====================================
// ==================================== A ====================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int f, s, n, cnt;
//pair<int, int> nums[1000005]; // NOLINT
//
//int main() {
//    cin >> f >> s >> n;
//
//    for (int i = 1; i <= n; i ++) { cin >> nums[i].second; }
//    for (int i = 1; i <= n; i ++) { cin >> nums[i].first; }
//
//    sort(nums + 1, nums + n + 1);
//
//    for (int i = 1; i <= n; i ++) {
//        if (f <= nums[i].second) {
//            cnt += nums[i].second - f + 1;
//            f += nums[i].second - f + 1;
//        }
//        if (s <= nums[i].first) {
//            cnt += nums[i].first - s + 1;
//            s += nums[i].first - s + 1;
//        }
//
//        f -= nums[i].second;
//        s += nums[i].first;
//    }
//
//    cout << cnt << endl;
//
//    return 0;
//}
// ==================================== B ====================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, ans;
//string s;
//
//int main() {
//    cin >> n >> s;
//    s = "0" + s;
//    while (true) {
//        int cnt = 0;
//
//        for (int i = 1; i < n; i ++) {
//            if (s[i] == 'S' && s[i + 1] == 'C') {
//                s[i] = 'C';
//                s[i + 1] = 'S';
//                cnt ++;
//                i ++;
//            }
//        }
//
//
//        if (!cnt) { break; }
//        ans ++;
//    }
//
//    cout << ans << endl;
//
//    return 0;
//}
// ==================================== C ====================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n;
//string start, target;
//string s1, s2;
//
//int main() {
//    cin >> n >> start >> target;
//
//    for (int i = 0; i < n; i ++) {
//        if (start[i] != '_') { s1 += start[i]; }
//        if (target[i] != '_') { s2 += target[i]; }
//    }
//
//    if (s1 == s2) { cout << "yes" << endl; }
//    else { cout << "no" << endl; }
//
//    return 0;
//}
// ==================================== D ====================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, m, gcd;
//int nums[100005], numsDivide[100005];
//
//int main() {
//    cin >> n >> m;
//    for (int i = 1; i <= n; i ++) { cin >> nums[i]; }
//    for (int i = 1; i <= m; i ++) { cin >> numsDivide[i]; }
//
//    sort(nums + 1, nums + 1 + n);
//
//    gcd = numsDivide[1];
//
//    for (int i = 1; i <= m; i ++) {
//        while (numsDivide[i] % gcd) { gcd --; }
//    }
//
//    for (int i = 1; i <= n; i ++) {
//        if (!(gcd % nums[i])) {
//            cout << i - 1 << endl;
//            return 0;
//        }
//    }
//
//    cout << -1 << endl;
//    return 0;
//}