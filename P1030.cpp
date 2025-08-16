#include <bits/stdc++.h>

using namespace std;

void dfs(string LDR, string LRD){//NOLINT
    if (LDR.empty() || LRD.empty()){
        return;
    }
    char root = LRD[LRD.size() - 1];
    cout << root;

    int mid = LDR.find(root);

    dfs(LDR.substr(0, mid), LRD.substr(0, mid));
    dfs(LDR.substr(mid + 1, LDR.size()), LRD.substr(mid, LDR.size() - 1 - mid));
}

int main(){
    string LDR, LRD;
    cin >> LDR >> LRD;
    dfs(LDR, LRD);
    return 0;
}