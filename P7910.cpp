#include <bits/stdc++.h>

using namespace std;

int n, Q, nums[20005];

int main(){
    cin >> n >> Q;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }
    for (int i = 1; i <= Q; i++){
        char operate;
        cin >> operate;
        if (operate == '1') {
            int x, v;
            cin >> x >> v;
            nums[x] = v;
        }
        else{
            int x;
            cin >> x;
            int indexes[10005];
            for (int j = 0; j <= n; j++){
                indexes[j] = j;
            }
            for (int j = x; j >= 2; j--){
                if (nums[j] < nums[j - 1]) {
                    int t = nums[j - 1];
                    int t_index = indexes[j - 1];
                    nums[j - 1] = nums[j];
                    indexes[j - 1] = indexes[j];
                    nums[j] = t;
                    indexes[j] = t_index;
                }
            }
            cout << indexes[x];
        }
    }
    return 0;
}