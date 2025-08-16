#include<bits/stdc++.h>

using namespace std;

vector<int> missle;
vector<int> memory;

int block1(){
    map<int, int> m;
    pair<int, int> a(0, INT_MIN);
    pair<int, int> b(0, INT_MIN);
    int ans = 0;
    for (int i = missle.size() - 1; i >= 0; i--){
        for (int j = missle.size() - 1; j >= 0; j--){
            if (memory[j] < missle[i]){
                memory[j] = missle[i];
            }
            else{
                while(memory[j] > missle[i]){
                    memory.pop_back();
                }
                memory.push_back(missle[i]);
                ans++;
            }
        }
    }
    return max(memory);
}


int block2(){
    set<int> high;
    for (int i: missle){
        bool flag = false;
        for (int j: high){
            if (j >= i){
                flag = true;
                high.erase(j);
                high.emplace(i);
                break;
            }
        }
        if (!flag){
            high.emplace(i);
        }
    }
    return high.size();
}

vector<int> split(const string &str, const char &n = ' '){
    vector<int> a;
    string tmp = "";
    for (auto i: str){
        if (i == n){
            a.push_back(stoi(tmp));
            tmp.clear();
        }
        else{
            tmp += i;
        }
    }
    a.push_back(stoi(tmp));
    return a;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    getline(cin, s);
    missle = split(s);
    cout << block1() << endl << block2();
    return 0;
}
