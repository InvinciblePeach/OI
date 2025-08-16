#include <bits/stdc++.h>

using namespace std;

int n, cards[100005], Sum, average;
unsigned long long ans;

int main(){
    cin >> n;
    for (int i = 1; i <= n ; i++){
        cin >> cards[i];
        Sum += cards[i];
    }

    average = Sum / n;

    for (int i = 1; i <= n; i++){
        if (cards[i] > average){
            cards[i + 1] += cards[i] - average;
            ans ++;
        }
        else if (cards[i] < average){
            cards[i + 1] -= average - cards[i];
            ans ++;
        }
    }

    cout << ans;

    return 0;
}