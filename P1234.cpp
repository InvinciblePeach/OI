#include <bits/stdc++.h>

using namespace std;

int n, m, ans = 0;
char a[1005][1005];

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n ; i++){
        for (int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (a[i][j] == 'h'){
                if (a[i][j + 1] == 'e' && a[i][j + 2] == 'h' && a[i][j + 3] == 'e'){
                    ans++;
                }
                if (a[i][j - 1] == 'e' && a[i][j - 2] == 'h' && a[i][j - 3] == 'e'){
                    ans++;
                }
                if (a[i + 1][j] == 'e' && a[i + 2][j] == 'h' && a[i + 3][j] == 'e'){
                    ans++;
                }
                if (a[i - 1][j] == 'e' && a[i - 2][j] == 'h' && a[i - 3][j] == 'e'){
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}