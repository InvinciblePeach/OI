#include <bits/stdc++.h>

using namespace std;

int N;
int h[80005];
long long ans;
stack<int> C;       //NOLINT

int main(){
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> h[i];
    }
    C.push(0);
    for (int i = 1; i <= N; i++){
        while (h[i] >= h[C.top()] && C.size() > 1){
            C.pop();
        }
        ans += C.size();
        C.push(i);
    }
    cout << ans - N << endl;

    return 0;
}