#include <bits/stdc++.h>

using namespace std;

int T, fib[1000005], sums[1000005] = {0};

int main(){
    cin >> T;
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= 1000005; i++){
        fib[i] = (fib[i - 1] + fib[i - 2]) % 9;
    }
    for (int i = 1; i <= 1000005; i++) {
        sums[i] = (fib[i] + sums[i - 1]) % 9;
    }
    for (int i = 1; i <= T; i++){
        int n;
        cin >> n;
        cout << sums[n] % 9 << endl;
    }
    return 0;
}