#include <bits/stdc++.h>

using namespace std;

int n, k;
pair<int, int> s[100005], a[100005], b[100005]; // NOLINT

bool cmp(const pair<int, int> & x, const pair<int, int> & y){
    return x.second < y.second;
}

int main(){

    cin >> n;

    for (int i = 1; i <= n; i++){
        cin >> s[i].first;
        s[i].second = i;
    }

    sort(s + 1, s + n + 1);

    k = !(n % 3) ? n / 3 : n / 3 + 1;

    for (int i = 1; i <= k; i++){
        a[i].second = b[i].second = s[i].second;
        a[i].first = i - 1;
        b[i].first = s[i].first - a[i].first;
    }

    for (int i = k + 1; i <= n - k; i++){
        a[i].second = b[i].second = s[i].second;
        b[i].first = i - 1;
        a[i].first = s[i].first - b[i].first;
    }

    for (int i = n - k + 1; i <= n; i++){
        a[i].second = b[i].second = s[i].second;
        b[i].first = n - i;
        a[i].first = s[i].first - b[i].first;
    }

    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + n + 1, cmp);

    cout << "YES" << endl;

    for (int i = 1; i <= n; i++){
        cout << a[i].first << ' ';
    }

    cout << endl;

    for (int i = 1; i <= n; i++){
        cout << b[i].first << ' ';
    }

    return 0;
}