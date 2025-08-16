#include <bits/stdc++.h>

using namespace std;

int n, m;
int nums[500005], tree[2000005], mark[2000005];

void push_down(int p, int len) {
    mark[p * 2] += mark[p];
    mark[p * 2 + 1] += mark[p];
    tree[p * 2] += mark[p] * (len - len / 2);
    tree[p * 2 + 1] += mark[p] * (len / 2);
    mark[p] = 0;
}

void push_up(int p) {
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
}

void build(int l, int r, int p) {
    if (l == r) { tree[p] = nums[l]; return; }

    int mid = (l + r) / 2;
    build(l, mid, p * 2);
    build(mid + 1, r, p * 2 + 1);

    push_up(p);
}

void update(int l, int r, int now_l, int now_r, int p, int d) {
    if (now_r < l || now_l > r) { return; }

    else if ( now_l >= l && now_r <= r) { mark[p] += d; tree[p] += d * (now_r - now_l + 1); }

    else {
        push_down(p, now_r - now_l + 1);

        int mid = (now_l + now_r) / 2;
        update(l, r, now_l, mid, p * 2, d);
        update(l, r, mid + 1, now_r, p * 2 + 1, d);

        push_up(p);
    }
}

int query(int l, int r, int now_l, int now_r, int p) {
    if (now_r < l || now_l > r) { return 0; }

    else if (now_l >= l && now_r <= r) { return tree[p]; }

    else {
        push_down(p, (now_r - now_l + 1));

        int mid = (now_l + now_r) / 2;

        return  query(l, r, now_l, mid, p * 2) + query(l, r, mid + 1, now_r, p * 2 + 1);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) { cin >> nums[i]; }
    build(1, n, 1);
    for (int i = 1; i <= m; i ++) {
        int opr, x, y;
        cin >> opr >> x >> y;
        if (opr == 1) { update(x, x, 1, n, 1, y); }
        else { cout << query(x, y, 1, n, 1) << endl; }
    }
    return 0;
}