#include <bits/stdc++.h>

using namespace std;

int n;
long long ans = LLONG_MIN, S = 0;
vector<pair<int, int>> cows;

bool cmp(pair<int, int> a, pair<int, int> b){
    return a.first + a.second < b.first + b.second;
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        int w, s;
        cin >> w >> s;
        cows.emplace_back(make_pair(w, s));
    }

    sort(cows.begin(), cows.end(), cmp);

    for (auto i : cows){
        ans = max(ans, S - i.second);
        S += i.first;
    }

    cout << ans << endl;

    return 0;
}