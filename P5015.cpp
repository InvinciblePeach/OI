#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    int len = 0;
    getline(cin, s);
    for (int i = 0; i < s.size(); i++){
        if (s[i] != ' '){
            len++;
        }
    }
    cout << len;
    return 0;
}
