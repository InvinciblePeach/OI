#include<bits/stdc++.h>

using namespace std;

const int n = 5;
int ans;
string s;
vector<char> v = {'@', '~', '!', '%', '#'};

string itob(int i){
    string str;
    while (n <= i){
        str.push_back(v[i % n]);
        i /= n;
    }
    str.push_back(v[i % n]);
    return str;
}

int main(){
    cin >> s;
    string tmp = "";
    for (char i: s){
        if (i == '+' || i == '-'){
            ans += stoi(tmp);
            tmp = "";
        }
        tmp.push_back(i);
    }
    ans += stoi(tmp);
    string ITOB = itob(ans);
    for (auto i = ITOB.rbegin(); i != ITOB.rend(); i++){
        cout << *i;
    }
    return 0;
}
