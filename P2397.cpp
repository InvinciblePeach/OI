#include <bits/stdc++.h>

using namespace std;

int ans = INT_MIN, cnt = 0, N, num;

int main(){
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> num;
        if (ans == num){
            end_++;
        }
        else if (end_ == 0){
            ans = num;
            cnt = 1;
        }
        else{
            cnt --;
        }
    }
    cout << ans << endl;
    return 0;
}