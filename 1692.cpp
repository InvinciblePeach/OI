#include <bits/stdc++.h>

using namespace std;

int n;
map<string, int> dic;
char operate;
string s;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> operate;
        cin >> s;
        if (operate == 'I'){
            if (dic.find(s) == dic.end()){
                dic[s] = 1;
            }
            else{
                dic[s] += 1;
            }
        }
        else{
            if (dic.find(s) == dic.end()){
                cout << 0 << endl;
            }
            else{
                cout << dic[s] << endl;
            }
        }
    }
    return 0;
}