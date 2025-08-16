#include<bits/stdc++.h>

using namespace std;

int n, m, q, v[65], w[65], items[65][3];
int dp[32005];

int main(){
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        cin >> v[i] >> w[i] >> q;
        w[i] = w[i] * v[i];

        if (!q) { items[i][0] = i; }
        else if (!items[q][1]) { items[q][1] = i; }
        else { items[q][2] = i; }
    }

    for (int i = 1; i <= m; i++) {
        if (!items[i][0]) { continue; }
        for (int j = n; j >= v[items[i][0]]; j--) {
            dp[j] = max({dp[j],

                    dp[j - v[items[i][0]]] + w[items[i][0]],

                    (j - v[items[i][0]] - v[items[i][1]] >= 0) ?
                    dp[j - v[items[i][0]] - v[items[i][1]]] + w[items[i][0]] + w[items[i][1]] : 0,

                    (j - v[items[i][0]] - v[items[i][2]] >= 0) ?
                    dp[j - v[items[i][0]] - v[items[i][2]]] + w[items[i][0]] + w[items[i][2]] : 0,

                    (j - v[items[i][0]] - v[items[i][1]] - v[items[i][2]] >= 0) ?
                    dp[j - v[items[i][0]] - v[items[i][1]] - v[items[i][2]]] + w[items[i][0]] + w[items[i][1]] + w[items[i][2]] : 0});
        }
    }

    cout << dp[n] << endl;
    return 0;
}
