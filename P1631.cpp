#include<bits/stdc++.h>

using namespace std;

int n, ans[100005] = {0}, a[100005], b[100005];
priority_queue<int> heap; // NOLINT


int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i < n; i++){
        cin >> b[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = a[i] + b[j];
            if (heap.size() <= n) {
                heap.push(x);
            } else if (heap.top() > x) {
                heap.pop();
                heap.push(x);
            } else {
                break;
            }
        }
    }

    for (int i = n; i >= 1; i--){
        ans[i] = heap.top();
        heap.pop();
    }

    for (int i = 1; i <= n; i++){
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}
