#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 8;
int n, m, s[MAXN], c[MAXN];
ld ans, p[MAXN];

struct Node {
    ld val;
    int i, k;

    Node() {}
    Node(int Val, int I, int K) : val(Val), i(I), k(K) {}

    bool operator<(Node const &o) const { return val < o.val; }
};
priority_queue<Node> q;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> s[i] >> c[i] >> p[i];
        p[i] /= 100;
    }

    for(int i = 0; i < n; i++)
        if (p[i] > 0)
            q.emplace(s[i] * p[i] / c[i], i, 1);

    while(!q.empty()){
        auto [val, i, k] = q.top();
        q.pop();
        if (m < c[i]) continue;

        ld t = s[i] * p[i] * pow(1.0 - p[i], k-1);
        ans += t, m -= c[i];

        ld d = t * (1.0 - p[i]);
        if (d > 1e-15) q.emplace(d / c[i], i, k + 1);
    }

    cout << ans << "\n";

    return 0;
}
