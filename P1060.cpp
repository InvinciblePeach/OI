#include<bits/stdc++.h>

using namespace std;

int n, m, v[30], w[30];
int f[30005] = {0};

int main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        cin >> v[i] >> w[i];
        w[i] *= v[i];
    }
    for (int i = 1; i <= m; i++){
        for (int j = n; j >= v[i]; j--){
            f[j] = max(f[j - v[i]] + w[i], f[j]);
        }
    }
    cout << f[n] << endl;
    return 0;
}
