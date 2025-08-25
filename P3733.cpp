#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010, MAXM = 2010, INF = 0x3f3f3f3f;
int n, m, q, cnt, tot, num, hd[MAXN], to[MAXM], nxt[MAXM], tim[MAXN], op[MAXN], ed[MAXN], bkw[MAXN];
bitset<MAXN> d[MAXN], dis[MAXN], val[MAXN], vis, w[MAXM];
pair<int, int> nw[MAXN];

void add(int u, int v, bitset<MAXN> w) {
    nxt[cnt] = hd[u];
    to[cnt] = v, ::w[cnt] = bitset<MAXN>(w);
    hd[u] = cnt++;
}

bitset<MAXN> in() {
    string s;
    cin >> s;
    return bitset<MAXN>(s);
}

void out(const bitset<MAXN> x) {
    bool stt = false;
    for (int i = 1000; ~i; i--) {
        if (x[i]) stt = true;
        if (stt) putchar('0' + x[i]);
    }
    if (!stt) putchar('0');
    puts("");
}

void adde(int u, int v, bitset<MAXN> w) { add(u, v, w), add(v, u, w); }

void insert(int nw, bitset<MAXN> x) {
    for (int i = 1000; ~i; i--) {
        if (!x[i]) continue;
        if (tim[i] < nw) swap(tim[i], nw), swap(x, d[i]);
        if (!nw) break;
        x ^= d[i];
    }
}

void query(int nw) {
    bitset<MAXN> res;
    for (int i = 1000; ~i; i--)
        if (tim[i] > nw && !res[i]) res ^= d[i];
    out(res);
}

void dfs(int u) {
    vis[u] = 1;
    for (int i = hd[u]; ~i; i = nxt[i]) {
        if (vis[to[i]]) insert(INF, dis[u] ^ dis[to[i]] ^ w[i]);
        else dis[to[i]] = dis[u] ^ w[i], dfs(to[i]);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    memset(hd, -1, sizeof(hd)), num = q + 1;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v, adde(u, v, in());
    }

    dfs(1);
    query(0);

    for (int i = 1, x, y; i <= q; i++) {
        static string s;
        cin >> s;
        if (s == "Add") {
            cin >> x >> y;
            op[i] = ++tot;
            val[tot] = (in() ^ dis[x] ^ dis[y]);
            nw[tot] = make_pair(x, y), bkw[tot] = tot;
        } else if (s == "Change") {
            cin >> x;
            ed[bkw[x]] = i, op[i] = --num;
            val[num] = (dis[nw[x].first] ^ dis[nw[x].second] ^ in());
            bkw[x] = num;
        } else if (s == "Cancel")
            cin >> x, ed[bkw[x]] = i;
    }
    for (int i = 1; i <= q; i++)
        if (!ed[i]) ed[i] = INF;
    for (int i = 1; i <= q; i++) {
        if (op[i]) insert(ed[op[i]], val[op[i]]);
        query(i);
    }

    return 0;
}