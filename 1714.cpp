#include <bits/stdc++.h>

using namespace std;

int n, now_s, cnt = 0, ans = 0, s, e;
bool flag = false;
vector<pair<int, int>> interval;

int main(){
    cin >> s >> e;
    cin >> n;
    now_s = s;

    for (int i = 1; i <= n; i++){
        int l, r;
        cin >> l >> r;
        interval.emplace_back(make_pair(l, r));
    }

    sort(interval.begin(), interval.end());

    for (int i = 0; i < n; i++){
        int j = i, max_r = INT_MIN;
        while (j < n && interval[j].first <= now_s){
            max_r = max(max_r, interval[j].second);
            j++;
        }
        if (max_r < now_s){
            break;
        }
        ans ++;
        if (max_r >= e){
            flag = true;
            break;
        }

        now_s = max_r;
        i = j - 1;
    }
    cout << (flag ? ans : -1) << endl;
    return 0;
}