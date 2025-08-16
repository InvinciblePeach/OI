#include<bits/stdc++.h>

using namespace std;

int v, n, c, k, m;
int f[10005] = {0};

int main(){
    cin >> v >> n >> c;
    for (int i = 1; i <= n; i++){
        cin >> k >> m;
        for (int j = c; j >= m; j--){
            f[j] = max(f[j - m] + k, f[j]);
        }
    }
    for (int i = 0; i <= c; i++){
        if (f[i] >= v){
            cout << v - i << endl;
            return 0;
        }
    }
    cout << "Impossible" << endl;
    return 0;
}
