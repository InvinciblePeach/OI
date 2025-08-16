#include <bits/stdc++.h>

using namespace std;

unsigned int N, M, dp[2][(1u << 10u) + 1][(1u << 10u) + 1], cnt[(1u << 10u) + 1], ground[105] = {0};
vector<unsigned int> s;

bool is_valid(unsigned int num){
    for (unsigned int i = 0; i < M; i++){
        if ( (num >> i & 1u) && ((num >> (i + 1u) & 1u) || (num >> (i + 2u) & 1u)) ){
            return false;
        }
    }
    return true;
}

unsigned int count(unsigned int num){
    unsigned int ans = 0;
    for (unsigned int i = 0; i < M; i++){
        ans += num >> i & 1u;
    }
    return ans;
}

int main(){
    cin >> N >> M;
    for (unsigned int i = 1u; i <= N; i++){
        for (unsigned int j = 0u; j < M; j++){
            char a;
            cin >> a;
            if (a == 'H'){
                ground[i] += 1u << j;
            }
        }
    }

    for (int i = 0; i < 1u << M; i++){
        if (is_valid(i)){
            s.push_back(i);
            end_[i] = count(i);
        }
    }

    for (unsigned int i = 1; i <= N + 2; i++){
        for (auto j : s){
            for (auto k : s){
                for (auto l : s){
                    if ((j & k) || (k & l) || (l & j)){
                        continue;
                    }
                    if ((ground[i] & j ) || (ground[i - 1] & k)){
                        continue;
                    }
                    dp[i % 2][j][k] = max(dp[i % 2][j][k], dp[(i - 1) % 2][k][l] + end_[j]);
                }
            }
        }
    }

    cout << dp[(N + 2) % 2][0][0] << endl;

    return 0;
}