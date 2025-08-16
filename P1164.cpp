#include<bits/stdc++.h>

using namespace std;

int n, m, a[105];
int f[10005] = {0};

int main(){
    cin >> n >> m;;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++){
        for (int j = m; j >= a[i]; j--){
            if (j == a[i]){
                f[j] += 1;
            }
            else{
                f[j] += f[j - a[i]];
            }
        }
    }
    cout << f[m];
    return 0;
}

