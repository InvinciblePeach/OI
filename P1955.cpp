#include <bits/stdc++.h>

using namespace std;

int T, n;
int pre[1000005];

int get(int x) {
    if (x == pre[x]) { return x; }
    return pre[x] = get(pre[x]);
}

void merge(int x, int y) {
    pre[get(x)] = get(y);
}

int main() {
    cin >> T;
    while (T --> 0) {
        cin >> n;
        for (int i = 1; i <= n; i ++) { pre[i] = i; }
    }
    return 0;
}