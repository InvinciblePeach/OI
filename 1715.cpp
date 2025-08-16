#include <bits/stdc++.h>

using namespace std;

int n, times[100005];
unsigned long long ans = 0;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> times[i];
    }

    sort(times + 1, times + n + 1);

    for (int i = 1; i <= n; i++){
        ans += times[i] * (n - i);
    }

    cout << ans << endl;

    return 0;
}