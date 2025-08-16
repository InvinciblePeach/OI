#include <bits/stdc++.h>

using namespace std;

int N, M, ans = INT_MAX;
int R[20], H[20], min_s[20], min_v[20];

void dfs(int u, int v, int s){
    if (u == 0) {
        if (v == N) {
            ans = min(ans, s);
        }
        return;
    }

    if (v + min_v[u] > N){
        return;
    }
    if (s + min_s[u] >= ans){
        return;
    }
    if (s + 2 * (N - v) /  R[u + 1] >= ans){
        return;
    }

    for (R[u] = min(R[u + 1] - 1, int(sqrt(N - v))); R[u] >= u ; R[u]--){
        for (H[u] = min(H[u + 1] - 1, (N - v) / R[u] / R[u]); H[u] >= u; H[u]--){
            int tmp = (u == M ? R[u] * R[u] : 0);
            dfs(u - 1, v + R[u] * R[u] * H[u], s + 2 * R[u] * H[u] + tmp);
        }
    }
}

int main(){
    cin >> N >> M;
    for (int i = 1; i <= M; i++){
        min_v[i] = min_v[i - 1] + i * i * i;
        min_s[i] = min_s[i - 1] + 2 * i * i;
    }

    R[M + 1] = H[M + 1] = INT_MAX;

    dfs(M, 0, 0);

    cout << ans << endl;

    return 0;
}
