#include <bits/stdc++.h>

using namespace std;

//struct edge {
//    int v, w;
//
//    edge(int v_, int w_) { v = v_, w = w_; }
//};

int n, num[105];
int a[105], d[105];
bool visited[105];
//vector<edge> graph[105];

int merge(int x, int y) {
    int tmp = num[x];
    for (int i = 1; i <= n; i ++) {
        if (num[i] == tmp) { num[i] = num[y]; }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        num[i] = i;
    }
    for (int i = 1; i <= n; i ++) {
        cin >> d[i];
        if (i - d[i] >= 1) { merge(i, i - d[i]); }
        if (i + d[i] <= n) { merge(i, i + d[i]); }
    }

    for (int i = 1; i <= n; i ++) {
        if (num[i] != num[a[i]]) { cout << "NO" << endl; return 0; }
    }
    cout << "YES" << endl;
    return 0;
}