#include <bits/stdc++.h>

using namespace std;

bool visited[100005] = {false};
int n, sum, max_, len, seg[100005];

bool dfs(int cnt, int now_len, int start, int fail){
    if (cnt == 0){
        return true;
    }
    for (int i = start; i <= n; i ++){

        if (visited[i] || seg[i] == fail){
            continue;
        }

        if (now_len + seg[i] <= len){
            visited[i] = true;
            if (now_len + seg[i] < len){
                if (dfs(cnt, now_len + seg[i], i + 1, fail)){
                    return true;
                }
            }
            if (now_len + seg[i] == len){
                if (dfs(cnt - 1, 0, 1, -1)){
                    return true;
                }
            }
            visited[i] = false;
            fail = seg[i];

            if (now_len == 0 || now_len + seg[i] == len){
                return false;
            }
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> seg[i];
        sum += seg[i];
        max_ = max(max_, seg[i]);
    }

    sort(seg + 1, seg + n + 1, greater<>());

    for (len = max_; len <= sum; len ++){
        if (sum % len){ continue;}
        if (dfs(sum / len, 0, 1, -1)){
            break;
        }
    }

    cout << len << endl;
    return 0;
}