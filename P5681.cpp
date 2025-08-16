#include <bits/stdc++.h>

using namespace std;

unsigned long long a, b, c;

int main(){
    cin >> a >> b >> c;
    if (a * a > b * c){
        cout << "Alice";
    }
    else{
        cout << "Bob";
    }
    return 0;
}