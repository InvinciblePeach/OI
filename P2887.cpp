#include <bits/stdc++.h>

using namespace std;

int C, L;
unsigned long long ans;
vector<pair<int, int>> cows;
vector<pair<int, int>> SPF;

bool cmp(pair<int, int> i, pair<int, int> j){
    return i.second < j.second;
}

int main(){
    cin >> C >> L;

    for (int i = 1; i <= C; i++){
        int l, r;
        cin >> l >> r;
        cows.emplace_back(make_pair(l, r));
    }

    for (int i = 1; i <= L; i++){
        int SPFi, n;
        cin >> SPFi >> n;
        SPF.emplace_back(make_pair(SPFi, n));
    }

    sort(cows.begin(), cows.end(), cmp);
    sort(SPF.begin(), SPF.end());

    for (auto i : cows){
        for (auto & j : SPF){
            if (j.second > 0 && j.first >= i.first && j.first <= i.second){
                j.second --;
                ans ++;
                break;
            }
        }
    }

    cout << ans << endl;

    return 0;
}