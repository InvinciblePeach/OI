#include<bits/stdc++.h>

using namespace std;

int N, V, v[35], f[20005];

int main(){
    cin >> V;
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> v[i];
    }
    for (int i = 1; i <= N; i++){
        for (int j = V; j >= v[i]; j--){
            if (f[j - v[i]] + v[i] > f[j]){
                f[j] = f[j - v[i]] + v[i];
            }
        }
    }
    cout << V - f[V];
    return 0;
}
