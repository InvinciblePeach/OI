#include<bits/stdc++.h>

using namespace std;

long long T, M;
long long f[100000005], t[1000005], v[1000005];

int main(){
    cin >> T >> M;
    for (int i = 1; i <= M; i++){
        cin >> t[i] >> v[i];
    }
    for (int i = 1; i <= M; i++){
        for (int j = t[i]; j <= T; j++){
            f[j] = max(f[j - t[i]] + v[i], f[j]);
        }
    }
    cout << f[T];
    return 0;
}
