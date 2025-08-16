#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    cin >> n;
    if (n % 2 || n == 2) { cout << "NO" << endl; }
    else if (!(n % 2)) { cout << "YES" << endl; }
    return 0;
}