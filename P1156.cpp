#include <bits/stdc++.h>

using namespace std;

int D, G, dp[110] = {-1};
tuple<int, int, int> litters[110]; // NOLINT

bool cmp(const tuple<int, int, int> & a, const tuple<int, int, int> & b){
    return get<0>(a) < get<0>(b);
}

int main(){
    dp[0] = 10;
    cin >> D >> G;
    for (int i = 1; i <= G; i++){
        int T, F, H;
        cin >> T >> F >> H;
        litters[i] = make_tuple(T, F, H);
    }

    sort(litters + 1, litters + G + 1, cmp);

    for (int i = 1; i <= G; i++){
        for (int j = D; j >= 0; j--){
            if (dp[j] >= get<0>(litters[i])){
                if (j + get<2>(litters[i]) >= D){
                    cout << get<0>(litters[i]) << endl;
                    return 0;
                }
                dp[j + get<2>(litters[i])] = max(dp[j], dp[j + get<2>(litters[i])]);
                dp[j] += get<1>(litters[i]);
            }
        }
    }

    cout << dp[0] << endl;
    return 0;
}