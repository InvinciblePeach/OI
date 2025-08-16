#include <bits/stdc++.h>

using namespace std;

int N, M, w[13005], d[13005];
int f[13005] = {0};

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i ++) {
        cin >> w[i] >> d[i];
    }
    for (int i = 1; i <= N; i ++) {
        for (int j = M; j >= w[i]; j --) {
            f[j] = max(f[j - w[i]] + d[i], f[j]);
        }
    }
    cout << f[M];
    return 0;
}
