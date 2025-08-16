#include<bits/stdc++.h>
// AC

using namespace std;

int n;
vector<int> a = {0};

vector<int> ms(){
    vector<int> ans;
    stack<int> s;
    for (int i = n; i > 0; i--){
        while (!s.empty()){
            if (a[s.top()] > a[i]){
                ans.insert(ans.begin(), s.top());
                s.push(i);
                break;
            }
            else{
                s.pop();
            }
        }
        if (s.empty()){
            ans.insert(ans.begin(), 0);
            s.push(i);
        }
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        a.push_back(x);
    }
    for (int i: ms()){
        cout << i << ' ';
    }
    return 0;
}
