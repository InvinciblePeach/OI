#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

signed main() {
    system("g++ gen.cpp -O2 -o gen");
    system("g++ std.cpp -O2 -std=c++14 -o std");
    system("g++ tmp.cpp -O2 -std=c++14 -fsanitize=address,undefined,leak -g");

    for (int i = 1; i <= 100; i++) {
        cout << "=====" << i << "=======\n";
        system("./gen > tmp.in");
        system("./std < tmp.in > std.out");
        if (system("./a.out < tmp.in > my.out")) return cout << "RE\n", 0;
        if (system("diff std.out my.out -Z")) return cout << "WA\n", 0;
        cout << "AC\n";
    }

    return 0;
}