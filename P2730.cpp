#include <bits/stdc++.h>

using namespace std;

string target;
string base = "12345678"; //NOLINT

unordered_map<string, int> dis;
unordered_map<string, pair<string, char>> pre;

string operatorA(const string & state) {
    string up = state.substr(0, 4);
    string down = state.substr(4, 4);
    reverse(up.begin(), up.end());
    reverse(down.begin(), down.end());
    return down + up;
}

string operatorB(const string & state) {
    return state[3] + state.substr(0, 3) + state.substr(5, 3) + state[4];
}

string operatorC(const string & state) {
    string _;
    return _ + state[0] + state[6] + state[1] + state[3] + state[4] + state[2] + state[5] + state[7];
}

void bfs(const string & start) {
    queue<string> q;
    q.emplace(start);
    dis[start] = 0;
    while (!q.empty()) {
        string state = q.front();
        q.pop();

        if (state == target) {
            return;
        }

        string ops[3];
        ops[0] = operatorA(state);
        ops[1] = operatorB(state);
        ops[2] = operatorC(state);

        for (int i = 0; i <= 2; i ++) {
            string now_state = ops[i];
            if (!dis.count(now_state)) {
                dis[now_state] = dis[state] + 1;
                pre[now_state] = make_pair(state, i + 'A');
                q.emplace(now_state);
            }
        }
    }
}

int main() {

    for (int i = 1; i <= 8; i ++) {
        char c;
        cin >> c;
        target += c;
    }

    if (base == target) {
        cout << 0 << endl;
    } else {
        bfs(base);
        cout << dis[target] << endl;
        string ans;
        while (target != base) {
            ans = pre[target].second + ans; //NOLINT
            target = pre[target].first;
        }
        cout << ans << endl;
    }
    return 0;
}