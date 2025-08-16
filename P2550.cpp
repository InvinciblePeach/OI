#include <bits/stdc++.h>

using namespace std;

int n, cnt, reward[7] = {0};
bool nums[35] = {false};

int main(){
    cin >> n;
    for (int i = 1; i <= 7; i++){
        int x;
        cin >> x;
        nums[x] = true;
    }
    for (int i = 1; i <= n; i++){
        cnt = 0;
        for (int j = 1; j <= 7; j++){
            int x;
            cin >> x;
            if (nums[x]){
                cnt++;
            }
        }
        reward[cnt]++;
    }
    for (int i = 7; i >= 1; i--){
        cout << reward[i] << ' ';
    }
    cout << endl;
}