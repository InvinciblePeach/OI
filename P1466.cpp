#include<bits/stdc++.h>

using namespace std;

int n;
int f[400] = {0};

int main(){
    cin >> n;
    int sum = ((1 + n) * n) / 2;
    if (sum % 2 == 1){
        cout << 0;
        return 0;
    }
    f[1] = 1;                                      // the ways of 1 item, "1" in bag
    for (int i = 2; i <= n; i++){
        for (int j = sum / 2; j > i; j--){
            f[j] = f[j] + f[j - i];                // f[j]: take it    f[j-i]: not take it
        }
    }
    cout << f[sum / 2];
    return 0;
}
