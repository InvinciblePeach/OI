#include <bits/stdc++.h>

using namespace std;

int a, b, c, d, e, f, g, h, i;

int main(){
    cin >> a >> b >> c >> d >> e >> f >> g >> h >> i;
    if (h){
        if (a + b + c + d + e + f + g + 55 >= i){
            cout << "AKIOI" << endl;
            return 0;
        }
    }
    else{
        if (a + b + c + d + e + f + g + 50 >= i){
            cout << "AKIOI" << endl;
            return 0;
        }
    }
    cout << "AFO" << endl;
    return 0;
}