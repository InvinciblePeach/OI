#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, m, a[MAXN];

struct Node {
    int lz, sum, val, add, mul;
    int son[2], fa;

    Node() {
        lz = sum = val = add = son[0] = son[1] = fa = 0;
        mul = 1;
    }
} t[MAXN];

#define fa(x) t[x].fa
#define lc(x) t[x].son[0]
#define rc(x) t[x].son[1]

bool get(int p) { return p == rc(fa(p)); }
bool isroot(int p) { return (lc(fa(p)) ^ p) && (rc(fa(p)) ^ p); }
void pushup(int p) { t[p].sum = t[lc(p)].sum ^ t[rc(p)].sum ^ t[p].val; }

void pushdown(int p) {
    if (!t[p].lz) return;
    swap(lc(p), rc(p)), t[lc(p)].lz ^= 1, t[rc(p)].lz ^= 1, t[p].lz = 0;
}

void update(int p) {
    if (!isroot(p)) update(fa(p));
    pushdown(p);
}

void rotate(int x) {
    int y = fa(x), z = fa(y), c = get(x);
    if (!isroot(y)) t[z].son[get(y)] = x;
    fa(t[x].son[c ^ 1]) = y, t[y].son[c] = t[x].son[c ^ 1], t[x].son[c ^ 1] = y;
    fa(y) = x, fa(x) = z;
    pushup(y), pushup(x);
}

void splay(int p) {
    update(p);
    for (int f = fa(p); f = fa(p), !isroot(p); rotate(p))
        if (!isroot(f)) rotate(get(f) == get(p) ? f : p);
}

void access(int x) {
    for (int p = 0; x; p = x, x = fa(x))
        splay(x), rc(x) = p, pushup(x);
}

void makeroot(int p) { access(p), splay(p), t[p].lz ^= 1; }

int find(int p) {
    access(p), splay(p);
    while (pushdown(p), lc(p)) p = lc(p);
    return splay(p), p;
}

void link(int x, int y) {
    makeroot(x);
    if (find(y) ^ x) fa(x) = y;
}

void split(int x, int y) { makeroot(x), access(y), splay(y); }

void cut(int x, int y) {
    makeroot(x);
    if (find(y) == x && fa(y) == x && !lc(y)) fa(y) = rc(x) = 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> t[i].val;
    while (m --> 0) {
        static int op, x, y;
        cin >> op >> x >> y;
        if (op == 0) split(x, y), cout << t[y].sum << '\n';
        if (op == 1) link(x, y);
        if (op == 2) cut(x, y);
        if (op == 3) makeroot(x), splay(x), t[x].val = y;
    }

    return 0;
}