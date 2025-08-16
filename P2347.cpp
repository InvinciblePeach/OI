#include<bits/stdc++.h>

using namespace std;

int a[7];
int farmar[] = {0, 1, 2, 3, 5, 10, 20};
int f[1005] = {1};
int sum = 0;
int cnt = 0;

int main(){
    for (int i = 1; i <= 6; i++){
        cin >> a[i];
        sum += a[i] * farmar[i];
    }
    for (int i = 1; i <= 6; i++){
        for (int j = sum; j >= farmar[i]; j--){
            for (int k = 1; k <= a[i] && j >= k * farmar[i]; k++){
                f[j] += f[j - k * farmar[i]];
            }
        }
    }
    for (int i = 1; i <= sum; i++){
        if (f[i]){
            cnt++;
        }
    }
    cout << "Total=" << cnt << endl;
    return 0;
}
