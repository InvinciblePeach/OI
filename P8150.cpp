#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10;

uint64_t query(int l, int r);
uint64_t get(int x);

int hd, bk, len;

struct Node {
    int pre, nxt;
} t[MAXN];

int getk(int k) {
    int res = 0;
    for (int i = 1; i <= k; i++) res = t[res].nxt;
    return res;
}

void del(int x) {
    len--;
    t[t[x].pre].nxt = t[x].nxt;
    t[t[x].nxt].pre = t[x].pre;
}

void del(int l, int r) {
    int i = 0;
    while (i < l) i = t[i].nxt;
    for (; i <= r; i = t[i].nxt) del(i);
}

vector<uint32_t> recover(int n) {
    vector<uint32_t> res(n);
    for (int i = 1; i <= n; i++) t[i].pre = i - 1, t[i].nxt = i + 1;
    t[hd = 0].nxt = 1, t[bk = n + 1].pre = n, len = n;

    while (len > 2) {
        int l = t[hd].nxt, r = t[bk].pre, mid1 = getk(len / 3), mid2 = getk(len - len / 3 + 1);
        ll val1 = query(l, mid2 - 1) - query(l, mid1), val2 = query(mid1 + 1, r) - query(mid2, r);
        if (val1 < val2) del(mid2, r);
        else if (val1 > val2) del(l, mid1);
        else del(t[mid1].nxt, t[mid2].pre);
    }

    int id = 0;
    if (len == 1) id = t[hd].nxt, res[id - 1] = get(id);
    else {
        int l = t[hd].nxt, r = t[bk].pre;
        ll val1 = get(l), val2 = get(r);
        if (val1 < val2) res[l - 1] = val1, id = l;
        else res[r - 1] = val2, id = r;
    }

    ll lst = res[id - 1];
    for (int i = id + 1; i <= n; i++) {
        ll val = query(id, i) + res[id - 1];
        res[i - 1] = val - lst, lst = val;
    }
    lst = res[id - 1];
    for (int i = id - 1; i; i--) {
        ll val = query(i, id) + res[id - 1];
        res[i - 1] = val - lst, lst = val;
    }
    return res;
}