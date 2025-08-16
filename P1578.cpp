#include <bits/stdc++.h>

using namespace std;

int L, W, n, ans = 0;
pair<int, int> points[5005]; // NOLINT

bool cmp(pair<int, int> a, pair<int, int> b){
    return a.second < b.second;
}

int main(){
    cin >> L >> W;
    cin >> n;
    if (n == 0){
        cout << L * W << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++){
        cin >> points[i].first >> points[i].second;
    }
    points[++n].first = L; points[n].second = W;
    points[++n].first = 0; points[n].second = W;
    points[++n].first = L; points[n].second = 0;
    points[++n].first = 0; points[n].second = 0;

    sort(points + 1, points + n + 1);

    int l, r, u, d;

    for (int i = 1; i <= n; i++){
        l = points[i].first, u = W, d = 0;
        for (int j = i + 1; j <= n; j++){
            r = points[j].first;
            ans = max(ans, (r - l) * (u - d));
            if (points[j].second < points[i].second){
                d = max(d, points[j].second);
            } else {
                u = min(u, points[j].second);
            }
        }
    }

    for (int i = n; i >= 1; i--){
        l = points[i].first, u = W, d = 0;
        for (int j = i - 1; j >= 1; j--){
            r = points[j].first;
            ans = max(ans, (l - r) * (u - d));
            if (points[j].second < points[i].second){
                d = max(d, points[j].second);
            } else {
                u = min(u, points[j].second);
            }
        }
    }

    sort(points + 1, points + n + 1, cmp);

    for (int i = 1; i <= n - 1; i++){
        ans = max(ans, L * (points[i + 1].second - points[i].second));
    }

    cout << ans << endl;

    return 0;
}