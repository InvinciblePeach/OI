#include<bits/stdc++.h>

using namespace std;

int n;
int a[10][10][10] = {0};
vector<int> v;
set<string> s;

void dfs(int i = 0, int sum = 1, string str = "1"){
    if (i >= n - 1 && sum == 0){
        s.emplace(str);
        return;
    }
    else if (i >= n - 1){
        return;
    }
    dfs(i + 1, sum + v[i + 1], str + "+" + to_string(v[i + 1]));
    dfs(i + 1, sum - v[i + 1], str + "-" + to_string(v[i + 1]));
    if (str[i * 2 - 1] == '+'){
        dfs(i + 1, sum + (9 * v[i]) + v[i + 1], str + " " + to_string(v[i + 1]));
    }
    else if (str[i * 2 - 1] == '-'){
        dfs(i + 1, sum - (9 * v[i]) - v[i + 1], str + " " + to_string(v[i + 1]));
    }
    else if (i == 0){
        dfs(i + 1, sum + (9 * v[i]) + v[i + 1], str + " " + to_string(v[i + 1]));
    }
}


int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        v.push_back(i);
    }
    dfs();
    for (auto i = s.begin(); i != s.end(); i++){
        cout << *i << endl;
    }
    return 0;
}
