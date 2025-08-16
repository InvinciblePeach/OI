#include <bits/stdc++.h>

using namespace std;

const int P = 131;
unsigned long long N, cnt = 0;
vector<string> Hash;

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++){
        string s;
        cin >> s;
        Hash.push_back(s);
    }

    sort(Hash.begin(), Hash.end());

    for (int i = 1; i <= N; i++){
        if (Hash[i - 1] != Hash[i]){
            end_ ++;
        }
    }

    cout << end_ << endl;

    return 0;
}