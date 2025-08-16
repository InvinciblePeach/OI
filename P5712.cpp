#include <bits/stdc++.h>

using namespace std;

int n;

int main(){
    cin >> n;
    if (n >= 2){
        cout << "Today, I ate " << n << " apples." << endl;
    }
    else{
        cout << "Today, I ate " << n << " apple." << endl;
    }
    return 0;
}