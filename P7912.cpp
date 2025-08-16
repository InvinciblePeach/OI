#include <bits/stdc++.h>

using namespace std;

struct node {
    int v, head, type;
    node * nxt;

    node(int v_, int type_, int head_, node * nxt_) { v = v_, type = type_, head = head_, nxt = nxt_; }

    node() = default;
};

int n;

int main() {
    cin >> n;
    node head(0, -1, 0, nullptr);
    node &now = head;
    for (int i = 1; i <= n; i ++) {
        int a;
        cin >> a;
        if (now.type != a) {
            now.nxt = & node(i, a, i, nullptr);
        }
    }
    return 0;
}