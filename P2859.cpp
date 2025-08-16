#include <bits/stdc++.h>

using namespace std;

int N, cnt = 1, indexes[500010];
vector<pair<pair<int, int>, int>> cows; // first.fist a, first.second b, second index
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // NOLINT

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
    return a.first.first < b.first.first;
}

int main(){
    cin >> N;
    for (int i = 1; i <= N; i++){
        int a, b;
        cin >> a >> b;
        cows.emplace_back(make_pair(make_pair(a, b), i));
    }

    sort(cows.begin(), cows.end(), cmp);

    pq.push(make_pair(INT_MIN, 1));

    for (auto & i : cows){
        auto x = pq.top();
        if (x.first < i.first.first){
            pq.pop();
            indexes[i.second] = x.second;
            pq.push(make_pair(i.first.second, x.second));
        }
        else{
            indexes[i.second] = ++cnt;
            pq.push(make_pair(i.first.second, cnt));
        }
    }

    cout << cnt << endl;

    for (int i = 1; i <= N; i++){
        cout << indexes[i] << endl;
    }

    return 0;
}