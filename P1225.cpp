#include <bits/stdc++.h>
#define int unsigned

using namespace std;

int base, target;
int dis[(1u << 16u) + 1];
unordered_map<int, pair<int, string>> pre;
signed dx[] = {0, 1, -1, 0, 0};
signed dy[] = {0, 0, 0, 1, -1};

void bfs() {
    queue<int> q;
    q.emplace(base);
    dis[base] = 1;
    while (!q.empty()) {
        auto state = q.front();
        q.pop();

        if (state == target) {
            return;
        }

        for (int i = 0; i < 16; i++) {
            if (!(state & (1u << i))) {
                continue;
            } else {
                int x = i / 4, y = i % 4;

                for (int j = 1; j <= 4; j++) {
                    int now_x = x + dx[j], now_y = y + dy[j];

                    if (now_x < 0 || now_x >= 4 || now_y < 0 || now_y >= 4) { continue; }
                    if (state & (1u << (now_x * 4 + now_y))) { continue; }

                    int now_state = state;

                    now_state ^= 1u << i;
                    now_state ^= 1u << (now_x * 4 + now_y);

                    if (dis[now_state]) { continue; }

                    string ans;
                    pre[now_state] = make_pair(state, ans + char(x + '1') + char(y + '1') + char(now_x + '1') +
                                                      char(now_y + '1'));
                    dis[now_state] = dis[state] + 1;
                    q.emplace(now_state);
                }
            }
        }
    }
}

signed main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char c;
            cin >> c;
            base |= unsigned(c - '0') << (i * 4 + j);
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char c;
            cin >> c;
            target |= unsigned(c - '0') << (i * 4 + j);
        }
    }

    bfs();

    cout << dis[target] - 1 << endl;

    stack<string> s;
    while (target != base) {
        s.emplace(pre[target].second);
        target = pre[target].first;
    }

    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }

    return 0;
}