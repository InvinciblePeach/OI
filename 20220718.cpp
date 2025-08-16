//#include <bits/stdc++.h>
//
//using namespace std;
//
//int this_money, money = 0, mom_money = 0;
//
//int main(){
//    for (int i = 1; i <= 12; i ++) {
//        cin >> this_money;
//        money += 300 - this_money;
//        if (money < 0){
//            cout << '-' << i << endl;
//            return 0;
//        }
//        mom_money += money / 100 * 100;
//        money -= money / 100 * 100;
//    }
//    cout << money + mom_money + mom_money * 0.2 << endl;
//    return 0;
//}
//======================================= B ==============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, schools[3005], classes[3005], unhappy = 0, ans = 0;
//
//int main(){
//    cin >> n;
//    for (int i = 1; i <= n; i++){
//        cin >> schools[i] >> classes[i];
//    }
//    for (int i = 1; i <= n; i++){
//        unhappy = unhappy + (schools[i] + classes[i]) - 8;
//        ans += unhappy;
//    }
//    cout << ans << endl;
//    return 0;
//}
//======================================= C ==============================================
#include <bits/stdc++.h>

using namespace std;

int n;
string nums[25];
string s;

bool cmp(const string & a, const string & b){
    return a + b > b + a;
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> nums[i];
    }
    sort(nums, nums + 25, cmp);
    for (auto & i : nums){
        cout << i;
    }
    return 0;
}
//======================================= D ==============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n = 0;
//string ans, s;
//char a[] = {'@', '~', '!', '%', '#'};
//
//int main(){
//    cin >> s;
//
//    string tmp = "+";
//    for (char i : s){
//        if (i == '+' || i == '-'){
//            n += stoi(tmp);
//            tmp = i;
//        }
//        else {
//            tmp += i;
//        }
//    }
//    n += stoi(tmp);
//
//    while (n){
//        ans = a[n % 5] + ans; // NOLINT
//        n /= 5;
//    }
//    cout << ans << endl;
//    return 0;
//}
//======================================= Div.2 B ==============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n = 1, ans = 0, nums[40];
//string s;
//
//int main(){
//    cin >> s;
//    string tmp;
//    for (auto & i : s){
//        if (i == ','){
//            nums[n++] = stoi(tmp);
//            tmp = "";
//        }
//        else{
//            tmp += i;
//        }
//    }
//    nums[n] = stoi(tmp);
//
//    int min_ = INT_MAX;
//    for (int i = 1; i <= n; i++){
//        min_ = min(min_, nums[i]);
//    }
//    for (int i = 1; i <= n; i++){
//        ans += nums[i] - min_;
//    }
//
//    cout << ans << endl;
//
//    return 0;
//}
//======================================= Div.2 C ==============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//long long n, ans = 0, times[100005] = {0}, sums[100005] = {0};
//
//int main(){
//    cin >> n;
//    for (int i = 1; i <= n; i++){
//        cin >> times[i];
//    }
//
//    sort(times + 1, times + 1 + n);
//
//    for (int i = 2; i <= n; i++){
//        sums[i] = sums[i - 1] + times[i - 1];
//        ans += sums[i];
//    }
//
//    cout << ans << endl;
//
//    return 0;
//}
//======================================= Div.2 D ==============================================
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, ans = 0;
//bool a[100005] = {false};
//
//int main(){
//    cin >> n;
//    for (int i = 2; i <= n; i++){
//        if (!a[i]){
//            for (int j = i * 2; j <= n; j += i){
//                a[j] = true;
//            }
//        }
//    }
//
//    while (n != 1){
//        for (int i = 2; i <= n; i++){
//            if (!a[i]){
//                if (n % i == 0) {
//                    ans++;
//                    n /= i;
//                }
//            }
//        }
//    }
//
//    cout << ans << endl;
//
//    return 0;
//}