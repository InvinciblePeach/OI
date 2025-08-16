#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

signed main() {
    system("g++ gen.cpp -O2 -o gen");
    system("g++ std.cpp -O2 -o std");
    system("g++ abc410d.cpp -O2");
    for (int i = 1; 1; i++) {
        cout << "==========" << i << "=========\n";
        system("./gen > tmp.in");
        system("./std < tmp.in > std.out");
        system("./a.out < tmp.in > my.out");
        if (system("diff  std.out  my.out -Z")) {
            cout << "WA\n";
            return 0;
        }
        cout << "AC\n";
    }

    return 0;
}