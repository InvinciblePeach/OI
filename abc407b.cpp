#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
int x, y, cnt;

int main() {
    cin >> x >> y;
    
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++)
            if (i + j >= x || abs(i - j) >= y)
                cnt++;
    printf("%.9LF\n", ld(cnt) / 36.0);
    return 0;
}