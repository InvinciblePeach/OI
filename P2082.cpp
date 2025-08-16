#include<bits/stdc++.h>

using namespace std;

int n, a, b, ans = 0;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a >> b;
        ans += abs(b - a) + 1;
    }
    cout << ans;
}
