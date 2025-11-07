#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e6 + 10;
int n, q, tot, nxt[25][MAXN], sum[25][MAXN], siz[MAXN], dep[MAXN];
int t[MAXN];
string s[MAXN][2];

int num(char a, char b) { return int(a - 'a') * 26 + (b - 'a'); }

struct Edge {
    int nxt, to;
    int w;
} e[MAXN];
int hd[MAXN], cnt;

void add(int u, int v, int w) {
    e[++cnt] = {hd[u], v, w};
    hd[u] = cnt;
}

int getedge(int u, int w) {
    for (int i = hd[u]; i; i = e[i].nxt)
        if (e[i].w == w) return e[i].to;
    return 0;
}

void emplace(int *t, int len) {
    int rt = 0;
    for (int i = 0, c; i < len; i++) {
        c = t[i];
        int v = getedge(rt, c);
        if (!v) add(rt, v = ++tot, c);
        // cerr << rt << ' ' << v << ' ' << c << '\n';
        rt = v;
    }
    // if (len == 1 && t[0] == num('g', 's')) cerr << rt << '\n';
    siz[rt]++;
}

void dfs(int u) {
    sum[0][u] = siz[nxt[0][u]];
    for (int i = 1; i < 25; i++)
        sum[i][u] = sum[i - 1][u] + sum[i - 1][nxt[i - 1][u]], nxt[i][u] = nxt[i - 1][nxt[i - 1][u]];
    for (int i = hd[u]; i; i = e[i].nxt) {
        auto w = e[i].w;
        int tmp = nxt[0][u];
        while (tmp && !getedge(tmp, w)) tmp = nxt[0][tmp];
        nxt[0][e[i].to] = getedge(tmp, w);
        if (nxt[0][e[i].to] == e[i].to) nxt[0][e[i].to] = 0;
        dep[e[i].to] = dep[u] + 1;
        dfs(e[i].to);
    }
}

void build() {
    queue<int> q;
    for (int i = hd[0]; i; i = e[i].nxt) q.emplace(e[i].to), dep[e[i].to] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        sum[0][u] = siz[nxt[0][u]];
        for (int i = 1; i < 25; i++)
            sum[i][u] = sum[i - 1][u] + sum[i - 1][nxt[i - 1][u]], nxt[i][u] = nxt[i - 1][nxt[i - 1][u]];
        for (int i = hd[u]; i; i = e[i].nxt) {
            auto w = e[i].w;
            int tmp = nxt[0][u];
            while (tmp && !getedge(tmp, w)) tmp = nxt[0][tmp];
            nxt[0][e[i].to] = getedge(tmp, w);
            dep[e[i].to] = dep[u] + 1;
            q.emplace(e[i].to);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> s[i][0] >> s[i][1];
        for (int j = 0; j < s[i][0].size(); j++) t[j] = num(s[i][0][j], s[i][1][j]);
        emplace(t, s[i][0].size());
    }
    build();
    // for (int i = 1; i <= tot; i++) cerr << nxt[0][i] << " \n"[i == tot];
    for (int i = 1; i <= q; i++) {
        string h[2];
        cin >> h[0] >> h[1];
        if (h[0].size() ^ h[1].size()) {
            cout << "0\n";
            continue;
        }
        int k = h[0].size();
        int l = 0, r = k - 1;
        while (h[0][l] == h[1][l]) l++;
        while (h[0][r] == h[1][r]) r--;
        for (int j = 0; j < k; j++) t[j] = num(h[0][j], h[1][j]);
        int rt = 0, res = 0;
        for (int j = 0; j < k; j++) {
            int v = getedge(rt, t[j]);
            while (rt && !v) rt = nxt[0][rt], v = getedge(rt, t[j]);
            rt = v;
            if (j >= r && dep[rt] >= j - l + 1) {
                res += siz[rt];
                auto u = rt;
                for (int p = 24; ~p; p--)
                    if (dep[nxt[p][u]] >= j - l + 1) res += sum[p][u], u = nxt[p][u];
            }
        }
        // cerr << '\n';
        cout << res << '\n';
    }
    return 0;
}