#include <bits/stdc++.h>

using namespace std;

unsigned long long ans = 1, x, n;

int main(){
    cin >> x >> n;
    for (int i = 1; i <= n; i++){
        ans += ans * x;
    }
    cout << ans << endl;
    return 0;
}